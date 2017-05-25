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

	temp=""

	for((j = 0; j < ${#arr[@]}; j++))
	do
		if [ "`stat -c %F ${arr[$j]}`" != "디렉토리" ]
		then
			for((k = `expr $j + 1`; k < ${#arr[@]}; k++))
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

	for((index__lastdir = 0; index__lastdir < ${#arr[@]}; index__lastdir++))
	do
		if [ "`stat -c %F ${arr[$index__lastdir]}`" = "디렉토리" ]
		then
			lastdir=`expr $lastdir + 1`
		fi
	done

	for((m=lastdir; m < ${#arr[@]}; m++))
	do
		if [ "`stat -c %F ${arr[$m]}`" != "디렉토리" ] && [ "`stat -c %F ${arr[$m]}`" != "일반 파일" ] && [ "`stat -c %F ${arr[$m]}`" != "일반 빈 파일" ]
		then
			for((n = `expr $m + 1`; n < ${#arr[@]}; n++))
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

	for((index=lastdir; index < ${#arr[@]}; index++))
	do
		if [ "`stat -c %F ${arr[$index]}`" = "일반 파일" ] || [ "`stat -c %F ${arr[$index]}`" = "일반 빈 파일" ]
		then
			lastnorfile=`expr $lastnorfile + 1`
		fi	
	done

	lastnorfile=`expr $lastnorfile + $lastdir`

	#각각 정렬
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

	for((index_d = lastnorfile; index_d < ${#arr[@]}; index_d++))
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

PrintSide()
{
  sortArr "pre"

  cd ../
  
  if [ ${#arrPre[@]} -gt 20 ]
  then
	indx__pre=20
  else
	indx__pre=${#arrPre[@]}
  fi

  for((indx_pre = 0; indx_pre < indx__pre; indx_pre++))
  do
	if [ "`stat -c %F ${arrPre[$indx_pre]}`" = "디렉토리" ]
	then
		if [ ${#arrPre[$indx_pre]} -gt 10 ]
		then
			tput cup `expr $indx_pre + 2` 1
			echo [34m"...."
		else
			tput cup `expr $indx_pre + 2` 1
			echo [34m"${arrPre[$indx_pre]}"
		fi
	
	elif [ "`stat -c %F ${arrPre[$indx_pre]}`" = "일반 파일" ] || [ "`stat -c %F ${arrPre[$indx_pre]}`" = "일반 빈 파일" ]
	then
		if [ ${#arrPre[$indx_pre]} -gt 10 ]
		then
			tput cup `expr $indx_pre + 2` 1
			echo [0m"...."
		else
			tput cup `expr $indx_pre + 2` 1
			echo [0m"${arrPre[$indx_pre]}"
		fi
	else
		if [ ${#arrPre[$indx_pre]} -gt 10 ]
		then
			tput cup `expr $indx_pre + 2` 1
			echo [32m "...."
		else
			tput cup `expr $indx_pre + 2` 1
			echo [32m"${arrPre[$indx_pre]}"
		fi
	fi
  done
  
  cd $RTB
}

PrintCenter()
{
  sortArr "now"

  row=2
  col=21
  count=0

  for((center = 0; center < ${#arrNow[@]}; center++))
  do
	if [ "`stat -c %F ${arrNow[$center]}`" = "디렉토리" ]
	then
		tput cup $row $col
		echo [34m"     __"
		tput cup `expr $row + 1` $col
		echo [34m"/---/ |"
		tput cup `expr $row + 2` $col
		echo [34m"|  d  |"
		tput cup `expr $row + 3` $col
		echo [34m"-------"
		tput cup `expr $row + 4` $col
		echo [34m"${arrNow[$center]}"
	elif [ "`stat -c %F ${arrNow[$center]}`" = "일반 파일" ] || [ "`stat -c %F ${arrNow[$center]}`" = "일반 빈 파일" ]
	then
		if [ "`stat -c %a ${arrNow[$center]}`" -eq 775 ]
		then
			tput cup $row $col
                        echo [31m"_______"
                        tput cup `expr $row + 1` $col
                        echo [31m"|     |"
                        tput cup `expr $row + 2` $col
                        echo [31m"|  x  |"
                        tput cup `expr $row + 3` $col
                        echo [31m"-------"
                        tput cup `expr $row + 4` $col
                        echo [31m"${arrNow[$center]}"
		else
			tput cup $row $col
			echo [0m"_______"
			tput cup `expr $row + 1` $col
			echo [0m"|     |"
			tput cup `expr $row + 2` $col
			echo [0m"|  o  |"
			tput cup `expr $row + 3` $col
			echo [0m"-------"
			tput cup `expr $row + 4` $col
			echo [0m"${arrNow[$center]}"
		fi
	else
		tput cup $row $col
		echo [32m"_______"
		tput cup `expr $row + 1` $col
		echo [32m"|     |"
		tput cup `expr $row + 2` $col
		echo [32m"|  s  |"
		tput cup `expr $row + 3` $col
		echo [32m"-------"
		tput cup `expr $row + 4` $col
		echo [32m"${arrNow[$center]}"
	fi
	
	count=`expr $count + 1`
	if [ $count -ge 5 ]
	then
		count=0
		row=`expr $row + 5`
		col=21
	else
		col=`expr $col + 15`
	fi
  done
  
}

tput cup 1 0
echo [0m"================================================================================================"


for((side = 2; side < 37; side++))
do
	tput cup $side 0
	echo [0m"|"
	tput cup $side 20
	echo [0m"|"
	tput cup $side 95
	echo [0m"|"
done

tput cup 37 0
echo [0m"================================================================================================"


PrintSide
PrintCenter

tput cup 38 0