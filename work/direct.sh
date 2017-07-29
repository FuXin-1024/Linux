#########################################################################
# File Name: direct.sh
# Author: fx
# mail: 1007160080qq.com
# Created Time: Sat 29 Jul 2017 02:42:41 AM PDT
#########################################################################
#!/bin/bash

GetKey()
{
	akey=(0 0 0)

	cESC=`echo -ne "\033"`
	while :
	do
		read  -n 1 key
		echo $key

		akey[0]=${akey[1]}
		akey[1]=${akey[2]}
		akey[2]=$key

		if [[ ${akey[0]} == $cESC && ${akey[1]} == "[" ]]
		then
			if [[ $key == "A" ]];then echo KEYUP
			elif [[ $key == "B" ]];then echo KEDOWN
			elif [[ $key == "C" ]];then echo KEYLEFT
			elif [[ $key == "D" ]];then echo KEYRIGHT
			fi
		fi

	done
}



GetKey
