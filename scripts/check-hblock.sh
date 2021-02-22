 #!/bin/bash
if [ -f /etc/hosts.noad ]; then
    echo "enabled"
else
    echo "disabled"
fi
