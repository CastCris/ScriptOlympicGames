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

FILE_INPUT=""
FILE_OUTPUT=""

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
        flag_name=${i%${delimiter}*}
        flag_value=${i#*${delimiter}}
        if [[ $flag_value = $flag_name ]];then
            flag_value=0
        fi
        flags_value[$flag_name]=$flag_value
    done
    #
    for i in $flags_user;do
        flag_name=${i%${delimiter}*}
        flag_value=${i#*${delimiter}}
        if [[ $flag_value = $flag_name ]];then
            flag_value=1
        fi
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
    local input_standard="--file --path=. --language --flags -i -o -io"
    local input_user="$@"
    local values=($(get_flags "$input_standard" "$input_user"))
    # echo ${values[@]}

    local file=${values[0]}
    local file_path=(${values[1]})

    local language=${values[2]}
    local flags_addon=${values[3]}

    local file_input=${values[4]}
    local file_output=${values[5]}
    local file_io=${values[6]} # input & output

    ##
    file_path=($(find $file_path -type f -name $file))
    if [[ ${#file_path[@]} -gt 1 ]];then
        abort "Multuple file definitions"
    fi

    if [ -z ${file_path[0]} ] || [ ! -f "${file_path[0]}" ];then
        abort "Invalid path or undifined file"
    fi

    #
    if [[ $language = 0 ]];then
        language=${file#*.}
    fi
    if [[ ! " ${LANGUAGE_ABLE[@]} " =~ [[:space:]]$language[[:space:]] ]];then
        echo "The language $languge isn't able"
        exit
    fi

    #
    if [[ $flags_addon = 0 ]];then
        flags_addon=""
    fi

    #
    if [[ $file_io = 1 ]];then
        file_input=$file_io
    fi
    if [[ $file_io = 1 ]];then
        file_output=$file_io
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

    FLAGS_ADDON="$FLAGS_ADDON ${COMPILER_FLAGSADDON[$compiler]}"
    
    if [ ! -d $FILE_INPUT_NAME ];then
        touch $FILE_INPUT_NAME
    fi

    echo -e "$compiler $compiler_flags $FILE_PATH\n"
    if [[ " ${LANGUAGE_DYNAMIC[@]} " =~ [[:space:]]$language[[:space:]] ]];then
        run="$compiler $FILE_PATH $compiler_flags"
        if [[ $FILE_INPUT = 1 ]];then
            run="$run < \$FILE_INPUT"
        fi
        if [[ $FILE_OUTPUT = 1 ]];then
            run="$run > \$FILE_OUTPUT"
        fi

        echo $run
        eval "$run"

        exit
    fi
    ($compiler $compiler_flags $FILE_PATH $FLAGS_ADDON)
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
