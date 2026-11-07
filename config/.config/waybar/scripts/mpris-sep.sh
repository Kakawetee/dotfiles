#!/bin/bash
playerctl --follow status 2>/dev/null | while read -r s; do
    case "$s" in
        Playing|Paused) echo "<span font_size='x-large'>•</span>" ;;
        *) echo "" ;;
    esac
done
