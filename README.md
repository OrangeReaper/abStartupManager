abStartupManager
================

**This application should be considered as being [in perpetual beta](https://en.wikipedia.org/wiki/Perpetual_beta) and may contain bugs.**

abStartupManager is a VPN, Startup and Shutdown Manager written using Qt for Ubuntu Desktop. 

See the [Wiki](https://github.com/OrangeReaper/abStartupManager/wiki) for some additional notes on Ubuntu Desktop Security.

## abStartupManager Supports


- Running of the script when VPN Connects (for the first time)

- Connect to alternate Server if VPN disconnects

- Connection to VPN Server using .ovpn files (frontend for OpenVPN)

- Email notification when non requested VPN disconnect occurs

- Shutdown PC option with the ability to run the script before the shutdown

- Disconnect VPN on Quit

- Display connection state as *on top* icon for instant visibility of connection state

- VPN "Kill Switch" using ipTabes; NB use with care will overwrite tables!

## ToDo

- -Add 'About' dialogue

- TBC scan open file for virtual network device type (tune/taps/null)

- Deal with the case when all servers are blacklisted in the selected profile

- Deal with selected profile empty

## Changelog
**v0.107.x**
- Sets up VPN "Killswitch" using ipTables
- VPN connection can be (and Killswitch) can be enabled/disabled from menu

**v0.106.x**
- After VPN disconnect ping again for 5 secs to double check status

**v0.105.x**
- Improved/simpler logic

**v0.104.x**
- VPN Connection Logs and Shutdown Script Logging
- Changed method that detects VPN Disconnection
- User can blacklist servers (rather than delete them)

**v0.103.x**
- More settings improvements; User can now switch between profiles.

**v0.102.x**
- Improve Setting Display; Improve VPN Connection maintenance; Prompt for disconnect on quit.

**v0.101.x**
- Profiles can be added and removed (but can't be used yet).

## Requires

abStartupManager has the following dependancies

- [openvpn](https://www.ovpn.com/en) to be installed
- qt5-default

These can be installed as follows:

```
  $ sudo apt install -y openvpn qt5-default
```

## Warnings

abStartupManager is intended to run as a normal user but use some commands that require *sudo* rights. the file */etc/sudoers* could be modified to allow the user running abStartupManager the necessary permissions as follows:

```
  $ sudo visudo
```

Add the following lines

```
  USER ALL=(root) NOPASSWD: /usr/sbin/openvpn
  USER ALL=(root) NOPASSWD: /usr/bin/killall
  USER ALL=(root) NOPASSWD: /sbin/shutdown
  USER ALL = (root:root) NOPASSWD: /opt/*
```

Change *USER* to the user you wish to add the permission.

*NOTE:* If installing from the provided deb file then scrips will be placed in directory /opt

If you choose to run abStartupManager as from Ubuntu *Startup Applications* then, in keeping with any program that requires X to be initialised before running you should use a command similar to

```
/bin/bash -c "while [ ! xset q &>/dev/null ]; do sleep 5; done && /usr/bin/abStartupManager"
```

## Installation

[Download the deb file from here](https://github.com/OrangeReaper/abStartupManager/tree/master/deb) and install using (eg)

```
$ sudo dpkg -i /path/to/abStartupManager_0.103.2_amd64.deb
```

## Credits

- Mailer function courtesy [bluetiger9](https://github.com/bluetiger9) cf [SmtpClient-for-Qt](https://github.com/bluetiger9/SmtpClient-for-Qt)
