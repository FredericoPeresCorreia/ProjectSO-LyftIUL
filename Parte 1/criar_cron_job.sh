#!/bin/bash
crontab -l > newCron
echo "*/10 * * * * ~/projeto/dashboard.sh" >> newCron
crontab newCron
rm newCron
