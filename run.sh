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
    echo ${!flags_value[@]}
    for i in $flags_user;do
        flag_name=${i%$delimiter*}
        flag_value=${i#*$delimiter}
        if [[ ! " ${!flags_value[@]} " =~ [[:space:]]${flag_name}[[:space:]] ]];then
            echo $flag_name
            continue
        fi
        flags_value[$flag_name]=${flag_value}
    done


    for i in $flags_default;do
        flag_name=${i%$delimiter*}
        echo -n "${flags_value[$flag_name]} "
    done

}
get_flags "abcd=10 efg=234567890 b=opa rtyui" "abcd=2001 efg=20"
echo ""
