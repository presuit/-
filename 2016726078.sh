#!/bin/bash


IFS=$'\n'

declare -a arrPre=()
declare -a arrNow=()

sortArr()
{
  case "$1" in 
	pre) 
	 RTB=`pwd`	
	 cd ../;;
	now) 
	 cd ./;;
  esac

declare -a arr=(`ls`)

if [ "${#arr[@]}" -eq 1 ]
then
	arr[0]=${arr[0]}	
else
	var=0

	while [ -n "${arr[$var]}" ]
	do
		var=`expr $var + 1`
	done

	temp=""

	for((j = 0; j < var; j++))
	do
		if [ "`stat -c %F ${arr[$j]}`" != "디렉토리" ]
		then
			for((k = `expr $j + 1`; k < var; k++))
				do
			 		if [ "`stat -c %F ${arr[$k]}`" = "디렉토리" ]
					then
						temp=${arr[$j]}
						arr[$j]=${arr[$k]}
						arr[$k]=$temp
					fi
						
				done
		fi
	done

	lastdir=0

	while [ "`stat -c %F ${arr[$lastdir]}`" = "디렉토리" ]
	do
		lastdir=`expr $lastdir + 1`
	done

	for((m=lastdir; m < var; m++))
	do
		if [ "`stat -c %F ${arr[$m]}`" != "디렉토리" ] && [ "`stat -c %F ${arr[$m]}`" != "일반 파일" ] && [ "`stat -c %F ${arr[$m]}`" != "일반 빈 파일" ]
		then
			for((n = `expr $m + 1`; n < var; n++))
			do
				if [ "`stat -c %F ${arr[$n]}`" = "일반 파일" ] || [ "`stat -c %F ${arr[$n]}`" = "일반 빈 파일" ]
				then
					temp=${arr[$m]}
					arr[$m]=${arr[$n]}
					arr[$n]=$temp
				fi
			done
		fi
	done


	lastnorfile=0

	for((index=lastdir; index < var; index++))
	do
		if [ "`stat -c %F ${arr[$index]}`" = "일반 파일" ] || [ "`stat -c %F ${arr[$index]}`" = "일반 빈 파일" ]
		then
			lastnorfile=`expr $lastnorfile + 1`
		fi	
	done

	lastnorfile=`expr $lastnorfile + $lastdir`

	declare -a b=()

	for((index_b = 0; index_b < lastdir; index_b++))
	do
		b[$index_b]=${arr[$index_b]}
	done

	b=( $(for el_b in "${b[@]}"
		do
			echo $el_b
		done | sort
	))

	declare -a c=()
	index_cc=0

	for((index_c = lastdir; index_c < lastnorfile; index_c++))
	do
		c[$index_cc]=${arr[$index_c]}
		index_cc=`expr $index_cc + 1`
	done

	c=( $(for el_c in "${c[@]}"
		do
			echo $el_c
		done | sort
	))

	declare -a d=()
	index_dd=0

	for((index_d = lastnorfile; index_d < var; index_d++))
	do
		d[$index_dd]=${arr[$index_d]}
		index_dd=`expr $index_dd + 1`
	done

	d=( $(for el_d in "${d[@]}"
		do
			echo $el_d
		done | sort
	))
	#결합하는 부분

	index_a=0

	for((index_BtoA = 0; index_BtoA < index_b; index_BtoA++))
	do
		arr[$index_a]=${b[$index_BtoA]}
		index_a=`expr $index_a + 1`
	done

	for((index_CtoA = 0; index_CtoA < index_cc; index_CtoA++))
	do
		arr[$index_a]=${c[$index_CtoA]}
		index_a=`expr $index_a + 1`
	done

	for((index_DtoA = 0; index_DtoA < index_dd; index_DtoA++))
	do
		arr[$index_a]=${d[$index_DtoA]}
		index_a=`expr $index_a + 1`
	done

fi

#조건에 따라 분기 
case "$1" in
	pre) for((index_pre = 0; index_pre < ${#arr[@]}; index_pre++))
		do
			arrPre[$index_pre]=${arr[$index_pre]}
		done;;
	now) for((index_now = 0; index_now < ${#arr[@]}; index_now++))
		do
			arrNow[$index_now]=${arr[$index_now]}
		done;;
esac

if [ "$1" = "pre" ]
then
	cd $RTB
elif [ "$1" = "now" ]
then 
	cd ./
fi
}

sortArr "pre"
sortArr "now"

for el in "${arrPre[@]}"
do
	echo $el
done

for le in "${arrNow[@]}"
do
	echo $le
done
