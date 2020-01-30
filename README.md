abStartupManager
================

abStartupManager is a VPN, Startup and Shutdown Manager written using Qt for Ubuntu Desktop.

## abStartupManager Supports

- Running of script when VPN Connects (for the first time)

- Connect to alternate Server if VPN disconnects

- Connection to VPN Server using .ovpn files

- Email notification when non requested vpn disconnect occurs

- Shutdown PC option with ability to run script before shutdown

- Disconnect VPN on Quit

- Display connection state as 'on top' icon for instant visibility of connection state

## ToDo

- Add profiles (to allow switching between geographical regions)

- Add 'About' dialog

- Detect if connection to router is present and act accordingly

- remove unused setting 'priveligedDir'

- improve settings display

## Warnings

abStartupManager is intended to run as a normal user but use some commands that require ''sudo'' rights. the file ''/etc/sodoers'' could be modified to allow the user running abStartupManager the necessary permissions as follows:

```
  $ sudo visudo
```

Add the following lines

```
  USER ALL=(root) NOPASSWD: /usr/sbin/openvpn
  USER ALL=(root) NOPASSWD: /usr/bin/killall
```

Change ''USER'' to the user you wish to add the permission

## Credits

- Mailer function courtesy [bluetiger9](https://github.com/bluetiger9) cf [SmtpClient-for-Qt](https://github.com/bluetiger9/SmtpClient-for-Qt)
