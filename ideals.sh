#!/bin/bash

function start_container {
        docker run --name ideals -p 1017:1017 -e USER="$USER" -d dominate/idea-license-server
}
case $1 in
        start)
        start_container
        ;;
        restart)
        docker stop ideals
        docker rm ideals
        start_container
        ;;
        stop)
        docker stop ideals
        ;;
        *)
        echo "Usage: $0 (start|stop)"
        ;;
esac


