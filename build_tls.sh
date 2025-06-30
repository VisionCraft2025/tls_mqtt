#!/bin/bash
echo "Building TLS MQTT Publisher..."
qmake6 mqtt_pub.pro
make clean
make
echo "Publisher build complete"

echo "Building TLS MQTT Subscriber..."
qmake6 mqtt_sub.pro
make clean  
make
echo "Subscriber build complete"

echo "Build finished. Run with:"
echo "./mqtt_pub (for publisher)"
echo "./mqtt_sub (for subscriber)"