using System;
using System.Collections.Generic;
using System.IO;
using System.Windows;
using System.Xml.Serialization;

public enum ModOptions { DllMethodOnline, DllMethodAutoPatch, DllMethodAutoPatchNonPermanent, MCenters5, HookMethod }

[Serializable]
public class Patch
{
    public string Version { get; set; }
    public long DisableTrial { get; set; }
    private static long DefaultPattern = 0x0000012881B60F;
    public long EnableTrial { get; set; }
    public long DefaultValue { get; set; }
    public long Position { get; set; }

    public Patch() { }

    public Patch(string version, long disable, long enable, long defaultval, long pos)
    {
        Position = pos;
        Version = version;
        DisableTrial = disable;
        EnableTrial = enable;
        DefaultValue = defaultval;
    }

    public Patch(string version, long pos)
    {
        Version = version;
        Position = pos;
        DisableTrial = 0x90909000B0C031;
        EnableTrial = 0x90909001B0C031;
        DefaultValue = DefaultPattern;
    }
}

[Serializable]
public class Config
{
    private static readonly string ConfigFilePath = "C:\\ProgramData\\MCenters\\config.xml"; // Change to your desired file path

    public ModOptions SelectedMod { get; set; }

   
    [XmlIgnore]
    public Dictionary<string, Patch> MCenters5ReleaseMinecraftPatches { get; set; } = new Dictionary<string, Patch>();

    [XmlIgnore]
    public Dictionary<string, Patch> MCenters5PreviewMinecraftPatches { get; set; } = new Dictionary<string, Patch>();

    // Properties for serialization
    [XmlArray("ReleaseMinecraftPatches")]
    [XmlArrayItem("Patch")]
    public List<PatchEntry> SerializedReleaseMinecraftPatches { get; set; }

  
    [XmlArray("PreviewMinecraftPatches")]
    [XmlArrayItem("Patch")]
    public List<PatchEntry> SerializedPreviewMinecraftPatches{ get; set; }

    private static Config ConfigCache;

    // Save the current configuration to the config file
    public void Save()
    {
        SerializedPreviewMinecraftPatches = ConvertToPatchEntryList(MCenters5PreviewMinecraftPatches);
        SerializedReleaseMinecraftPatches = ConvertToPatchEntryList(MCenters5ReleaseMinecraftPatches);
        XmlSerializer serializer = new XmlSerializer(typeof(Config));
        using (StreamWriter writer = new StreamWriter(ConfigFilePath))
        {
            serializer.Serialize(writer, this);
        }
    }

    // Load the configuration from the config file
    public static Config Load()
    {
        if (ConfigCache != null) goto Exit;
        if (!File.Exists(ConfigFilePath))
        {
            ConfigCache = new Config(); // Return default config if file does not exist
            goto Exit;
        }

        XmlSerializer serializer = new XmlSerializer(typeof(Config));
        using (StreamReader reader = new StreamReader(ConfigFilePath))
        {
            ConfigCache = (Config)serializer.Deserialize(reader);
            goto Exit;
        }
    Exit:;
        ConfigCache.MCenters5PreviewMinecraftPatches = ConfigCache.ConvertToDictionary(ConfigCache.SerializedPreviewMinecraftPatches);
        ConfigCache.MCenters5ReleaseMinecraftPatches = ConfigCache.ConvertToDictionary(ConfigCache.SerializedReleaseMinecraftPatches);
        return ConfigCache;
    }

    // Convert Dictionary to List for serialization
    private List<PatchEntry> ConvertToPatchEntryList(Dictionary<string, Patch> patches)
    {
        var list = new List<PatchEntry>();
        foreach (var kvp in patches)
        {
            list.Add(new PatchEntry { Key = kvp.Key, Value = kvp.Value });
        }
        return list;
    }

    // Convert List back to Dictionary after deserialization
    private Dictionary<string, Patch> ConvertToDictionary(List<PatchEntry> patchEntries)
    {
        var dictionary = new Dictionary<string, Patch>();
        foreach (var entry in patchEntries)
        {
            dictionary[entry.Key] = entry.Value;
        }
        return dictionary;
    }
}

// Helper class for serialization
[Serializable]
public class PatchEntry
{
    public string Key { get; set; }
    public Patch Value { get; set; }
}
