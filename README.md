<p align='center'>
  <img src='https://github.com/tinedpakgamer/M-Centers-8.0/blob/master/MCenters/images/mcenter_5_icon.png?raw=true' alt='M Centers Logo' width="30%">
</p>
<h1 align='center'>M Centers 8th Edition</h1>
<p align='center'>A multi-method &amp; WIP (Stable, Safe & Working) unlocker for <em>Minecraft for Windows</em>, and any other programs that use the same licensing system as <em>Minecraft for Windows</em>.
</p>
<p align='center'>
<picture>
  <img alt="Last Release" src="https://img.shields.io/github/v/release/tinedpakgamer/M-Centers-8.0?include_prereleases">
</picture>
<picture>
  <img alt="Last Commit Date" src="https://img.shields.io/github/last-commit/tinedpakgamer/M-Centers-8.0">
</picture>
<picture>
  <img alt="Number of Open Issues" src="https://img.shields.io/github/issues-raw/tinedpakgamer/M-Centers-8.0">
</picture>
<picture>
  <img alt="Number of Open Pull Requests" src="https://img.shields.io/github/issues-pr/tinedpakgamer/M-Centers-8.0">
</picture>
<picture>
  <img alt="Number of Contributors" src="https://img.shields.io/github/contributors/tinedpakgamer/M-Centers-8.0">
</picture>
</p>

## Usage

### Requirements

  - Windows 10 or above.
  - An x64 or x86 CPU.

### Optional Requirements
  - [Microsoft Visual C++ Redistributable](https://aka.ms/vs/17/release/vc_redist.x64.exe), to be able to use some mod options in the app.
  - Minecraft for Windows, or the program to crack, the program that you need to crack is required by some of the mod options.

<h3>How to install M Centers and install the hack</h3>
<ol>
    <li>Download Minecraft: Bedrock Edition free trial by using the Microsoft Store or the <a href="https://www.xbox.com/games/store/minecraft-for-windows/9NBLGGH2JHXJ">Xbox</a> app, another way is to open Windows Run (Windows key + R) and type <strong>ms-windows-store://pdp/?ProductId=9NBLGGH2JHXJ</strong> to launch the Minecraft for Windows store page to let you download the free trial of Minecraft for Windows to unlock it.</li>
    <li>Download the <strong>latest</strong> version from <a href="https://mcenters.net/Downloads/M-Centers-8th-Edition/">the M Centers website</a></li>
    <li>Extract the files</li>
    <li>Open <strong>M Centers.exe</strong></li>
    <li>Select the 3rd option, by default it will say <strong>DLL Method Online</strong></li>
    <li>Select <strong>DLL Method Auto Patch (or any other mod option you want to use)</strong></li>
    <li>Press on the <strong>Activate</strong> button.</li>
    <li>Press on the <strong>Back</strong> button, to go to the main menu.</li>
    <li>Click <code>"Install Cracked DLL"</code></li>
    <li>Click <code>Start</code></li>
  </ol>
  
## FAQ
<ol>
<li><p>Why does it give me Unsupported Version?</p>

The unsupported version error occurs when you are using the DLL Online method, and the DLL for your version of Windows is not found on the repository you are using (either custom or either the official M Centers DLL repo), to fix this you need to use the DLL Auto Patch method, which will take your system DLLs rather than online ones and patch them.
</li>
<li><p>Are permanent DLL methods dangerous?</p>

To answer this question, DLL methods are not dangerous at all, as long as you use official, patched DLLs, such as the M Centers DLL repo or you can use the DLL Auto Patch method, and not 3rd party DLLs from 3rd party repos, if they do cause damage, then you can always Uninstall the DLL method with Uninstall Hack, and switch to a non-permanent method such as the M Centers 5 method, the DLL (Non-Permanent) method, or the Hook method.
</li>
<li><p>Why does it give Access to the path 'C:\Windows\System32\Windows.ApplicationModel.Store.dll' is denied or something similar?</p>

This is either because you didn't run M Centers as administrator, or your antivirus is falsely flagging M Centers and not allowing it to be accessed. You can fix it by running M Centers as administrator, disabling your antivirus. If this still didn't fix your problem, press the Uninstall Hack button in M Centers, then restart your computer, and try Install Hack again.
</li>
<li><p>Why does it give me System.IO.FileNotFoundException?</p>

System.IO.FileNotFoundException occurs when the system cannot find files, this might be happening because you didn't extract the .zip file and are running M Centers standalone without any of its files from the .zip file, to fix it, you need to extract the .zip file
</li>
<li><p>Why doesn't the DLL Auto Patch method work while running Windows Event Viewer?</p>

Please close Windows Event Viewer while running M Centers using the mode, <strong>DLL Auto Patch</strong>, it will cause the system licensing dll <strong>Windows.ApplicationModel.Store.dll</strong> to become non-readable.
</li>
<li><p>Why does it give me an error like finding Records.txt or similar in China?</p>

If you live in China, check if you can visit raw.githubusercontent.com directly, but if you meet a flashback or get an error like cannot find file <strong>Records.txt</strong>, then try and  make a hosts record manually, like so:
<code>185.199.108.133               raw.githubusercontent.com</code>
</li>
</ol>

## How to compile M Centers from the source code
- Clone the repository or download the repository to your device.
- [Download](https://visualstudio.microsoft.com/) and install Visual Studio 2022.
- Download and install .NET Desktop Development and Desktop development with C++ Workload in Visual Studio 2022.
- Open the 'M Centers 8.0.sln' file with Visual Studio 2022.
- Click on Build, and wait until it compiles M Centers.
- Go to the build folder of your project, and tada, you have compiled M Centers from the source code. 

### The folder structure of M Centers when compiled:
```
my-folder/                         # Root directory.
|- FluentWPF.dll                   # DLL file for FluentWPF library
|- M-Centers.exe                   # Main executable
|- M-Centers.exe .config           # Config file for M-Centers.exe
|- M Centers.pdb                   # PDB file for M Centers
|- MaterialDesignColors.dll        # DLL file for MaterialDesignColors library
|- MaterialDesignThemes.Wpf.dll    # DLL file for MaterialDesignThemes.Wpf library
|- MaterialDesignThemes.Wpf.xml    # XML file for MaterialDesignThemes.Wpf library
|- MCentersLibrary.dll             # DLL file for MCentersLibrary
|- MCentersLibrary.pdb             # PDB file for MCentersLibrary
```

## Contributors

<a href="https://github.com/tinedpakgamer/M-Centers-8.0/graphs/contributors">
  <img src="https://contrib.rocks/image?i=2&repo=tinedpakgamer/M-Centers-8.0"/>
</a>

## License

Read [LICENSE](LICENSE.MD) for the license that M Centers 8th Edition uses.

For any other licenses (such as 3rd party licenses), read [LICENSE.THIRDPARTY](LICENSE.THIRDPARTY).
