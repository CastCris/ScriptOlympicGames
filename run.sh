#!/bin/bash

## FLAGS
OPTION_FILE='--file'
OPTION_PATH='--path'
OPTION_LANGUAGE='--language'
OPTION_FLAGS_ADDON='--flags'

##
FILE_INPUT_NAME="input.txt"
FILE_OUTPUT_NAME="output.txt"
FILE_MAIN_NAME="main"

##
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

##
RED_COLOR='\e[0;31m'
YEL_COLOR='\e[0;33m'
NOR_COLOR='\e[0m'
##
FILE_PATH=""
LANGUAGE=""
FLAGS_ADDON=""

abort(){
    local message="$1"
    echo -e "$RED_COLOR$message$NOR_COLOR"
    exit
}


get_flags(){ # option mask | user input | delimter
    local flags_default="$1"
    local flags_user="$2"
    local delimiter="$3"
    if [[ ${#delimiter} -gt 1 ]] || [[ ${#delimiter} -eq 0 ]];then
        delimiter='='
    fi

    declare -A flags_value
    for i in $flags_default;do
        flags_value[${i%$delimiter*}]=${i#*$delimiter}
    done
    #
    for i in $flags_user;do
        flag_name=${i%$delimiter*}
        flag_value=${i#*$delimiter}
        if [[ ! " ${!flags_value[@]} " =~ [[:space:]]${flag_name}[[:space:]] ]];then
            continue
        fi
        flags_value[$flag_name]=${flag_value}
    done
    #
    for i in $flags_default;do
        flag_name=${i%$delimiter*}
        echo -n "${flags_value[$flag_name]} "
    done

}

check_command(){ # user input -> path_file \n language \n flags
    local input_standard="--file --path=. --language --flags"
    local input_user="$@"
    local values=($(get_flags "$input_standard" "$input_user"))

    local file=${values[0]}
    local file_path=(${values[1]})
    local language=${values[2]}
    local flags_addon=${values[3]}
    ##
    file_path=($(find $file_path -type f -name $file))
    if [[ ${#file_path[@]} -gt 1 ]];then
        abort "Multuple file definitions"
    fi

    if [ -z ${file_path[0]} ] || [ ! -f "${file_path[0]}" ];then
        abort "Invalid path or undifined file"
    fi

    #
    if [[ $language = $OPTION_LANGUAGE ]];then
        language=${file#*.}
    fi
    if [[ ! " ${LANGUAGE_ABLE[@]} " =~ [[:space:]]$language[[:space:]] ]];then
        echo "The language $languge isn't able"
        exit
    fi

    #
    if [[ $flags_addon = $OPTION_FLAGS_ADDON ]];then
        flags_addon=""
    fi

    #
    #
    FILE_PATH=$file_path
    LANGUAGE=$language
    FLAGS_ADDON=$flags_addon
}

main(){
    local input_user="$@"
    check_command "$input_user"

    local compiler=${LANGUAGE_COMPILER[$LANGUAGE]}
    local compiler_flags="${COMPILER_FLAGS[$compiler]}"

    FLAGS_ADDON="$FLAGS_ADDON ${COMPILER_FLAGSADDON[$compiler]}"
    
    if [ ! -d $FILE_INPUT_NAME ];then
        touch $FILE_INPUT_NAME
    fi

    echo -e "$compiler $compiler_flags $FILE_PATH\n"
    if [[ " ${LANGUAGE_DYNAMIC[@]} " =~ [[:space:]]$language[[:space:]] ]];then
        (($compiler $FILE_PATH $compiler_flags) < $FILE_INPUT_NAME) > $FILE_OUTPUT_NAME
        exit
    fi
    ($compiler $compiler_flags $FILE_PATH $FLAGS_ADDON) < $FILE_INPUT_NAME
    ./$FILE_MAIN_NAME < $FILE_INPUT_NAME > $FILE_OUTPUT_NAME
}

main "$@"
