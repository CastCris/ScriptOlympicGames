#!/bin/bash

## FLAGS
OPTION_PATH=
OPTION_EMPTY="0"
OPTION_INCLUDE="1"
OPTION_DELIMITER='#'

OPTION_DEFAULT="--file --path . --language --flags -i -o -io -f -p -l"

FLAG_VALID="1"
FLAG_INVALID="0"

## Default io files name
FILE_INPUT_NAME="input.txt"
FILE_OUTPUT_NAME="output.txt"
FILE_MAIN_NAME="main"

## Language Configuration
LANGUAGE_ABLE=(c cpp c++ py)
declare -A LANGUAGE_COMPILER=(
    ["c"]="gcc"
    ["cpp"]="g++"
    ["c++"]="g++"
    ["py"]="python3"
)
LANGUAGE_DYNAMIC=(py)

C_FLAGS='-Wall -Wextra -O2 -std=c99 -g'
CXX_FLAGS='-Wall -Wextra -O2 -std=c++20 -g'
PY_FLAGS=''
declare -A COMPILER_FLAGS=(
    ["gcc"]="$C_FLAGS"
    ["g++"]="$CXX_FLAGS"
    ["python3"]="$PY_FLAGS"
)

declare -A COMPILER_FLAGSADDON=(
    ["gcc"]="-o $FILE_MAIN_NAME -lm"
    ["g++"]="-o $FILE_MAIN_NAME"
    ["python3"]=""
)

## Color vars
RED_COLOR='\e[0;31m'
YEL_COLOR='\e[0;33m'
NOR_COLOR='\e[0m'

## Global vars
FILE_PATH=""
LANGUAGE=""
FLAGS_ADDON=""

FILE_INPUT=""
FILE_OUTPUT=""

# / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / #
abort(){
    local message="$1"
    echo -e "$RED_COLOR$message$NOR_COLOR"
    exit
}


IFS_change(){
    OIFS=$IFS
    IFS=$1
}

IFS_return(){
    IFS=$OIFS
}

##
flag_valid(){
    local string="$1"
    if [[ ${string:0:1} = '-' ]];then
        echo "$FLAG_VALID"
        return
    fi
    echo "$FLAG_INVALID"
    return
}

#
line_update(){ # update_line
    local arguments=($@)
    for i in `seq 1 $((${#arguments[@]}-1))`;do
        if [[ $(flag_valid ${arguments[$i]}) = $FLAG_INVALID ]];then
            continue
        fi
        echo ${arguments[@]:$i}
        break
    done
}


line_flag_name(){
    local arguments=($@)
    for i in ${arguments[@]};do
        if [[ $(flag_valid $i) = $FLAG_INVALID ]];then
            continue
        fi
        echo $i
        return
    done
    echo 0
}

line_flag_value(){
    local arguments=($1)
    local argument_empty_value=$2
    local index=1
    for i in `seq 1 $((${#arguments[@]}-1))`;do
        if [[ $(flag_valid ${arguments[$i]}) = $FLAG_VALID ]] && [[ $i = 1 ]];then
            echo "$argument_empty_value"
            return
        fi

        if [[ $(flag_valid ${arguments[$i]}) = $FLAG_VALID ]];then
            index=$(($i-1))
            break
        fi
    done

    if [[ $(flag_valid ${arguments[0]}) = $FLAG_INVALID ]] || [[ ${#arguments[@]} = 1 ]];then
        echo $argument_empty_value
        return
    fi

    for i in `seq 1 $index`;do
        if [[ ${arguments[$i]:0:1} = '\' ]];then
            echo -n ${arguments[$i]:1}
            continue
        fi
        echo -n ${arguments[$i]}
    done
}


line_flags_names(){
    local line="$@"
    while [[ ${#line} -gt 0 ]];do
        line_flag_name "$line"
        line="$(line_update "$line")"
    done
}

line_flags_values(){
    local line="$1"
    local option_empty="$2"
    while [[ ${#line} -gt 0 ]];do
        flag_value=$(line_flag_value "$line" "$option_empty")
        echo -n "$flag_value$OPTION_DELIMITER"
        line="$(line_update "$line")"
    done
    echo
}

line_flags_values_f(){ # option mask | user input
    local flags_default="$1"
    local flags_user="$2"

    declare -A flags_values
    flags_default_names=($(line_flags_names "$flags_default" $OPTION_EMPTY))
    flags_default_values="$(line_flags_values "$flags_default" $OPTION_EMPTY)"
    IFS_change $OPTION_DELIMITER
    flags_default_values=($flags_default_values)
    IFS_return

    #echo ${flags_default_names[@]}
    #echo ${flags_default_values[@]}

    for i in ${!flags_default_names[@]};do
        flag_name=${flags_default_names[$i]}
        flag_value=${flags_default_values[$i]}

        flags_values[$flag_name]=$flag_value
    done
    
    flags_user_names=($(line_flags_names "$flags_user" $OPTION_INCLUDE))
    flags_user_values="$(line_flags_values "$flags_user" $OPTION_INCLUDE)"
    IFS_change $OPTION_DELIMITER
    flags_user_values=($flags_user_values)
    IFS_return

    # echo ${flags_user_names[@]}
    # echo ${flags_user_values[@]}
    
    for i in ${!flags_user_names[@]};do
        flag_name=${flags_user_names[$i]}
        flag_value=${flags_user_values[$i]}
        if [[ ! " ${!flags_values[@]} " =~ [[:space:]]$flag_name[[:space:]] ]];then
            continue
        fi
        if [ -z "$flag_value" ];then
            continue
        fi

        flags_values[$flag_name]=$flag_value
    done

    for i in ${flags_default_names[@]};do
        echo "${flags_values[$i]}"
    done
}

get_no_empty_options(){
    local options=($@)
    for i in ${options[@]};do
        if [[ $i = $OPTION_EMPTY ]];then
            continue
        fi
        echo $i
        return
    done
    echo $OPTION_EMPTY
}

# / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / #
check_command(){ # user input -> path_file \n language \n flags
    local input_standard="$OPTION_DEFAULT"
    local input_user="$@"
    local values=($(line_flags_values_f "$input_standard" "$input_user"))

    local file=$(get_no_empty_options "${values[0]} ${values[7]}")
    local file_path=$(get_no_empty_options "${values[1]} ${values[8]}")

    local language=$(get_no_empty_options "${values[2]} ${values[9]}")
    local flags_addon=${values[3]}

    local file_input=$(get_no_empty_options "${values[4]} ${values[6]}")
    local file_output=$(get_no_empty_options "${values[5]} ${values[6]}")

    ##
    file_path=($(find $file_path -type f -name $file))
    if [[ ${#file_path[@]} -gt 1 ]];then
        abort "Multuple file definitions"
    fi

    if [ -z ${file_path[0]} ] || [ ! -f "${file_path[0]}" ];then
        abort "Invalid path or undifined file"
    fi

    #
    if [[ $language = $OPTION_EMPTY ]];then
        language=${file#*.}
    fi
    if [[ ! " ${LANGUAGE_ABLE[@]} " =~ [[:space:]]$language[[:space:]] ]];then
        echo "The language $languge isn't able"
        exit
    fi

    #
    if [[ $flags_addon = $OPTION_EMPTY ]];then
        flags_addon=""
    fi

    #
    FILE_PATH=$file_path
    LANGUAGE=$language
    FLAGS_ADDON=$flags_addon
    FILE_INPUT=$file_input
    FILE_OUTPUT=$file_output
}

main(){
    local input_user="$@"
    check_command "$input_user"

    local compiler=${LANGUAGE_COMPILER[$LANGUAGE]}
    local compiler_flags="${COMPILER_FLAGS[$compiler]}"

    FLAGS_ADDON="${COMPILER_FLAGSADDON[$compiler]} $FLAGS_ADDON"
    
    if [ ! -d $FILE_INPUT_NAME ];then
        touch $FILE_INPUT_NAME
    fi

    echo -e "$compiler $compiler_flags $FILE_PATH $FLAGS_ADDON\n"
    if [[ " ${LANGUAGE_DYNAMIC[@]} " =~ [[:space:]]$LANGUAGE[[:space:]] ]];then
        run="$compiler $FILE_PATH $compiler_flags"

        if [[ $FILE_INPUT = 1 ]];then
            run="$run < $FILE_INPUT_NAME"
        fi
        if [[ $FILE_OUTPUT = 1 ]];then
            run="$run > $FILE_OUTPUT_NAME"
        fi

        echo $run
        eval "$run"

        exit
    fi

    #
    ($compiler $compiler_flags $FILE_PATH $FLAGS_ADDON)
    if [[ $? -ne 0 ]];then
        abort "A compilation error occurs"
    fi

    run="./$FILE_MAIN_NAME"
    if [[ $FILE_INPUT = 1 ]];then
        run="$run < $FILE_INPUT_NAME"
    fi
    if [[ $FILE_OUTPUT = 1 ]];then
        run="$run > $FILE_OUTPUT_NAME"
    fi

    echo $run
    eval "$run"
}

main "$@"
# check_command "$@"
: '
echo "-"
while [[ ${#input_user} -gt 0 ]];do
    flag_name=$(flag_next_get "$input_user")
    flag_value=$(flag_value_get "$input_user")
    echo "Flag name $flag_name+"
    echo "Flag value $flag_value-"

    input_user="$(update_line "$input_user")"
    echo $input_user

    echo
done
echo "-"

input_standard="--file --path . --language --flags -i -o -io -f -p -l"
input_user="$@"
line_flags_names "$input_standard"
line_flags_values "$input_user" "$OPTION_DELIMITER"
line_flags_values_f "$input_standard" "$input_user"
'
