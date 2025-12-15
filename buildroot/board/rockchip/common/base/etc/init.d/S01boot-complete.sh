#!/bin/sh

### BEGIN INIT INFO
# Provides:          boot_complete
# Required-Start:
# Required-Stop:
# Should-Start:
# Should-Stop:
# Default-Start:     2
# Default-Stop:      0
# Short-Description: open flash led
# Description:       when system started, open flash led
### END INIT INFO

case "$1" in
        start)
                echo 1 > /proc/rp_system_flag/rp_boot_completed
                ;;
        stop)
                echo "no stop function"
                ;;
        restart)
                echo "no restart function"
                ;;
        *)
                echo "Usage: $0 {start|stop|restart}"
                exit 1
                ;;
esac

exit 0
