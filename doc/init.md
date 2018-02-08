Sample init scripts and service configuration for curved
==========================================================

Sample scripts and configuration files for systemd, Upstart and OpenRC
can be found in the contrib/init folder.

    contrib/init/curved.service:    systemd service unit configuration
    contrib/init/curved.openrc:     OpenRC compatible SysV style init script
    contrib/init/curved.openrcconf: OpenRC conf.d file
    contrib/init/curved.conf:       Upstart service configuration file
    contrib/init/curved.init:       CentOS compatible SysV style init script

1. Service User
---------------------------------

All three Linux startup configurations assume the existence of a "curvecore" user
and group.  They must be created before attempting to use these scripts.
The OS X configuration assumes curved will be set up for the current user.

2. Configuration
---------------------------------

At a bare minimum, curved requires that the rpcpassword setting be set
when running as a daemon.  If the configuration file does not exist or this
setting is not set, curved will shutdown promptly after startup.

This password does not have to be remembered or typed as it is mostly used
as a fixed token that curved and client programs read from the configuration
file, however it is recommended that a strong and secure password be used
as this password is security critical to securing the wallet should the
wallet be enabled.

If curved is run with the "-server" flag (set by default), and no rpcpassword is set,
it will use a special cookie file for authentication. The cookie is generated with random
content when the daemon starts, and deleted when it exits. Read access to this file
controls who can access it through RPC.

By default the cookie is stored in the data directory, but it's location can be overridden
with the option '-rpccookiefile'.

This allows for running curved without having to do any manual configuration.

`conf`, `pid`, and `wallet` accept relative paths which are interpreted as
relative to the data directory. `wallet` *only* supports relative paths.

For an example configuration file that describes the configuration settings,
see `contrib/debian/examples/curve.conf`.

3. Paths
---------------------------------

3a) Linux

All three configurations assume several paths that might need to be adjusted.

Binary:              `/usr/bin/curved`
Configuration file:  `/etc/curvecore/curve.conf`
Data directory:      `/var/lib/curved`
PID file:            `/var/run/curved/curved.pid` (OpenRC and Upstart) or `/var/lib/curved/curved.pid` (systemd)
Lock file:           `/var/lock/subsys/curved` (CentOS)

The configuration file, PID directory (if applicable) and data directory
should all be owned by the curvecore user and group.  It is advised for security
reasons to make the configuration file and data directory only readable by the
curvecore user and group.  Access to curve-cli and other curved rpc clients
can then be controlled by group membership.

3b) Mac OS X

Binary:              `/usr/local/bin/curved`
Configuration file:  `~/Library/Application Support/CurveCore/curve.conf`
Data directory:      `~/Library/Application Support/CurveCore`
Lock file:           `~/Library/Application Support/CurveCore/.lock`

4. Installing Service Configuration
-----------------------------------

4a) systemd

Installing this .service file consists of just copying it to
/usr/lib/systemd/system directory, followed by the command
`systemctl daemon-reload` in order to update running systemd configuration.

To test, run `systemctl start curved` and to enable for system startup run
`systemctl enable curved`

4b) OpenRC

Rename curved.openrc to curved and drop it in /etc/init.d.  Double
check ownership and permissions and make it executable.  Test it with
`/etc/init.d/curved start` and configure it to run on startup with
`rc-update add curved`

4c) Upstart (for Debian/Ubuntu based distributions)

Drop curved.conf in /etc/init.  Test by running `service curved start`
it will automatically start on reboot.

NOTE: This script is incompatible with CentOS 5 and Amazon Linux 2014 as they
use old versions of Upstart and do not supply the start-stop-daemon utility.

4d) CentOS

Copy curved.init to /etc/init.d/curved. Test by running `service curved start`.

Using this script, you can adjust the path and flags to the curved program by
setting the CURVED and FLAGS environment variables in the file
/etc/sysconfig/curved. You can also use the DAEMONOPTS environment variable here.

4e) Mac OS X

Copy org.curve.curved.plist into ~/Library/LaunchAgents. Load the launch agent by
running `launchctl load ~/Library/LaunchAgents/org.curve.curved.plist`.

This Launch Agent will cause curved to start whenever the user logs in.

NOTE: This approach is intended for those wanting to run curved as the current user.
You will need to modify org.curve.curved.plist if you intend to use it as a
Launch Daemon with a dedicated curvecore user.

5. Auto-respawn
-----------------------------------

Auto respawning is currently only configured for Upstart and systemd.
Reasonable defaults have been chosen but YMMV.
