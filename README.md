abStartupManager
================

**This application should be considered as being [in perpetual beta](https://en.wikipedia.org/wiki/Perpetual_beta) and may contain bugs.**

abStartupManager is a VPN, Startup and Shutdown Manager written using Qt for Ubuntu Desktop. 

See the [Wiki](https://github.com/OrangeReaper/abStartupManager/wiki) for some additional notes on Ubuntu Desktop Security.

## abStartupManager Supports

- Running of script when VPN Connects (for the first time)

- Connect to alternate Server if VPN disconnects

- Connection to VPN Server using .ovpn files (frontend for openvpn)

- Email notification when non requested vpn disconnect occurs

- Shutdown PC option with ability to run script before shutdown

- Disconnect VPN on Quit

- Display connection state as *on top* icon for instant visibility of connection state

## ToDo

- Add 'About' dialog

- Detect if connection to router is present and act accordingly

- Add logging (VPN Connection Logs)

- Add Logging (Shutdown Script Logging)

- TBC scan ovpn file for virtual network device type (tunX/tapX/null)

## Changelog

* v0.103.0 More settings improvements; User can now switch between profiles.

* v0.102.0 Improve Setting Display; Improve VPN Connection maintenance; Prompt for disconnect on quit.

* v0.101.0 Profiles can be added and removed (but can't be used yet).

## Requires

abStartupManager requires [openvpn](https://www.ovpn.com/en) to be installed, eg

```
  $ sudo apt install openvpn
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
```

Change *USER* to the user you wish to add the permission.

If you choose to run abStartupManager as from Ubuntu *Startup Applications* then, in keeping with any program that requires X to be initialised before running you should use a command similar to

```
/bin/bash -c "while [ ! xset q &>/dev/null ]; do sleep 5; done && /usr/bin/abStartupManager"
```

## Installation

[Download the deb file](https://github.com/OrangeReaper/abStartupManager/blob/master/deb/abStartupManager_0.103.2_amd64.deb) and install using (eg)

```
$ sudo dpkg -i /path/to/abStartupManager_0.103.2_amd64.deb
```

## Credits

- Mailer function courtesy [bluetiger9](https://github.com/bluetiger9) cf [SmtpClient-for-Qt](https://github.com/bluetiger9/SmtpClient-for-Qt)
