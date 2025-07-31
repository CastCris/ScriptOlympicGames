get_flags(){
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
main(){
    local input_standard="-file -path=. -language=c -flags"
    local input_user="$@"
    local values=$(get_flags "$input_standard" "$input_user")

    echo $values
}

main "$@"
