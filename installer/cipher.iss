[Setup]
AppName=Cipher
AppVersion=1.0
DefaultDirName={pf}\Cipher
DefaultGroupName=Cipher
OutputBaseFilename=cipher-installer
Compression=lzma
SolidCompression=yes

[Files]
; Main executable
Source: "build\cipher.exe"; DestDir: "{app}"; Flags: ignoreversion

; GTK DLLs copied from MSYS2 runtime
Source: "dist\*"; DestDir: "{app}"; Flags: recursesubdirs ignoreversion

[Icons]
Name: "{group}\Cipher"; Filename: "{app}\cipher.exe"
Name: "{commondesktop}\Cipher"; Filename: "{app}\cipher.exe"; Tasks: desktopicon

[Tasks]
Name: "desktopicon"; Description: "Create a Desktop icon"; GroupDescription: "Additional icons:"
