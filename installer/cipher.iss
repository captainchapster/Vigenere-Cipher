[Setup]
AppName=Cipher
AppVersion=1.0
DefaultDirName={pf}\Cipher
DefaultGroupName=Cipher
OutputBaseFilename=cipher-installer
Compression=lzma
SolidCompression=yes
ArchitecturesInstallIn64BitMode=x64
AllowNoIcons=yes

[Files]
; Main program
Source: "..\build\cipher.exe"; DestDir: "{app}"; Flags: ignoreversion

; GTK runtime (copied by GitHub Actions)
Source: "..\dist\*"; DestDir: "{app}"; Flags: recursesubdirs ignoreversion

[Icons]
Name: "{group}\Cipher"; Filename: "{app}\cipher.exe"
Name: "{commondesktop}\Cipher"; Filename: "{app}\cipher.exe"; Tasks: desktopicon

[Tasks]
Name: "desktopicon"; Description: "Create a Desktop shortcut"; GroupDescription: "Additional Tasks:";
