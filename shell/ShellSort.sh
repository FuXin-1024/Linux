#########################################################################
# File Name: ShellSort.sh
# Author: fx
# mail: 1007160080qq.com
# Created Time: Mon 31 Jul 2017 02:55:59 AM PDT
#########################################################################
#!/bin/bash

function ShellSort()
{
	arr=$1
	gap=$2
	local i end temp
	while [ $gap -gt 1 ]
	do
		(( gap = $gap/3 + 1 ))
		
		for (( i=gap; i<$2; i++ ))
		do
			(( end = $i - $gap ))
			(( temp = ${arr[i]}))
			while [ $end -ge 0 ]
			do
				if (( arr[end] < $temp ));then
					break;
				else
					(( arr[end+gap] = ${arr[$end]} ))
					(( end -= $gap))
				fi
			done
			(( arr[end+gap]=$temp ))
		done
	done
}

function Print()
{
	arr=$1
	len=$2
	local i
	for (( i=0;i<len;i++ ))
	do
		echo ${arr[i]}
	done
}
arr=(3 1 5 2 8 7 9 0 6 4)
Print $arr 10
ShellSort $arr 10
echo "after sort :"
Print $arr 10
