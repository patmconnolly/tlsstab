#!/usr/bin/bash

branch="$1"
basefilename="tlsstab"
year=$(date -u +%Y)
month=$(date -u +%m)
day=$(date -u +%d)
hour=$(date -u +%H)
minute=$(date -u +%M)

#Add each filename to be included in final package, separated by a space.
IncludedFilenames="$basefilename test_output.txt"

if [[ "$branch" == "development" ]]; then
	outputfile="$basefilename-$branch-$year.$month.$day-$hour.$minute.tar"
elif [[ "$branch" == "nightly" ]]; then
	outputfile="$basefilename-$branch-$year.$month.$day.tar"
elif [[ "$branch" == "stable" ]]; then
	outputfile="$basefilename-$branch-$year.$month.$day.tar"
fi


tar --owner 0 --group 0 -cvf $outputfile $IncludedFilenames
