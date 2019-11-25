#!/bin/bash
echo anticipatory | sudo tee /sys/block/sda/queue/scheduler
