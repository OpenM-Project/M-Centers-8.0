
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls.Primitives;


using System.Windows;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Runtime.InteropServices;
using System.Xaml;
using System.Windows.Controls;
using System.Configuration;
using System.Xml;
using System.Xml.Serialization;
using System.IO;

namespace MCenters
{
    internal class MCenters5
    {


        static readonly Config Config = Config.Load();




        public enum PrepareResults
        {
            StartError, StartFailed, InvalidVersion, Success, MemoryReadError, MemoryWriteError, MemoryPatternError, UnknownError
        };


        public class API
        {
           private static bool Search(Process process, FileVersionInfo fileVersion, bool isPreview)
            {
                Logger.StartOperation("Trying Pattern Search");
                uint FileSize = 0;
#if x64
                ulong ReadBytes = 0;
#elif x86
uint ReadBytes=0;
#endif
                FileSize = (uint)process.MainModule.ModuleMemorySize;
                Logger.Write("Reading Data Source " + process.MainModule.ModuleName);
                unsafe
                {
                    ReadBytes = MCentersLibrary.MCenters5.SetDataSource(process.Id, process.MainModule.BaseAddress.ToPointer(), (int)FileSize);
                }
                Logger.Write("Data Source Read bytes " + ReadBytes.ToString());
#if x64
                var isEqual = ReadBytes != (ulong)FileSize;
#elif x86
                var isEqual = ReadBytes != FileSize;
#endif
                if (isEqual)
                    return false;
                int count = 2;
                long offset = 2;


                count = -1;
                unsafe
                {
                    offset = MCentersLibrary.MCenters5.TryFindValue(&count, false);

                }

                Logger.Write("Count" + count.ToString());
                if (count != 1)
                {
                    return false;
                }
                var version = fileVersion.ProductVersion;
                var patch = new Patch(version, offset);

                if (isPreview)
                    Config.MCenters5PreviewMinecraftPatches.Add(version, patch);
                else
                    Config.MCenters5ReleaseMinecraftPatches.Add(version, patch);
                Config.Save();

                Logger.CompleteOperation("Trying Pattern Search");
                return true;

            }


            public static PrepareResults PrepareProcess(bool trial, bool launchPreviewEdition)
            {

                Process process = null;

                bool started = false;
                try
                {

                    int id = MCentersLibrary.MCenters5.LaunchApp(launchPreviewEdition);

                    process = id != 0 ? Process.GetProcessById(id) : process;
                    if (appId == 0)
                    {
                        appId = id;
                        process.EnableRaisingEvents = true;
                        process.Exited += API.OnExited;
                    }
                    if (process != null)
                        started = true;
                }
                catch (Exception e)
                {
                    Logger.Write("Error:\t\t" + e.Message);
                    return PrepareResults.StartError;

                }
                if (!started)
                {
                    Logger.Write("Error:\t\tMinecraft Start Failed. Is Minecraft Installed?");
                    return PrepareResults.StartFailed;
                }
                var fileVersion = process.MainModule.FileVersionInfo;
                var version = fileVersion.ProductVersion;
                if (!IsValidVersion(fileVersion, launchPreviewEdition))
                {
                    Logger.Write("Error:\t\tMinecraft version is not in known list");
                    Logger.Write("Using Pattern Mode");



                    var hasKey = launchPreviewEdition ?
                        Config.MCenters5PreviewMinecraftPatches.ContainsKey(version) :
                        Config.MCenters5ReleaseMinecraftPatches.ContainsKey(version);

                    if (hasKey)
                    {
                        Logger.Write("Found from config");
                    }
                    else
                    {

                        if (!Search(process, fileVersion, false))
                        {
                            Logger.Write("Pattern Error, Version Unsupported");
                            return PrepareResults.InvalidVersion;
                        }
                    }
                    Logger.Write("End Pattern Mode");

                }
                Patch patch;
                if (launchPreviewEdition)
                    Config.MCenters5PreviewMinecraftPatches.TryGetValue(version, out patch);
                else
                    Config.MCenters5ReleaseMinecraftPatches.TryGetValue(version, out patch);
                MCentersLibrary.MCenters5.ChangePatchValues(patch.DisableTrial, patch.EnableTrial, patch.DefaultValue, patch.Position);
                int result;
                unsafe
                {
                    result = MCentersLibrary.MCenters5.ModifyApp(process.Id, process.MainModule.BaseAddress.ToPointer(), trial, ignoreVerification);
                }
                switch (result)
                {
                    case 1:
                        ignoreVerification = true;
                        Logger.Write("Mode Injection Successful");
                        return PrepareResults.Success;
                    case -2:
                        Logger.Write("Error Occured While Reading Memory");
                        return PrepareResults.MemoryReadError;
                    case -3:
                    case -4:
                        Logger.Write("Error Occured While Writing Memory");
                        return PrepareResults.MemoryWriteError;
                    case 0:
                        Logger.Write("Unknown Memory Patterns\nYou may be using unsupported version\nor using other mods");
                        return PrepareResults.MemoryPatternError;
                    default:
                        Logger.Write("Unknown Error Occured");
                        return PrepareResults.UnknownError;
                }




            }


            static bool ignoreVerification = false;
            static int appId = 0;
            static bool IsValidVersion(FileVersionInfo info, bool isPreviewEdition)
            {
                var version = info.ProductVersion;
                var hasKey=isPreviewEdition?
                    Config.MCenters5PreviewMinecraftPatches.ContainsKey(version):
                    Config.MCenters5ReleaseMinecraftPatches.ContainsKey(version);
                Logger.Write("Detected Version: " + info.ProductVersion);
                return info.ProductName == "Minecraft" && hasKey;

            }
            static void OnExited(object sender, EventArgs e)
            {
                ignoreVerification = false;
                appId = 0;
            }
        };


    }






}

