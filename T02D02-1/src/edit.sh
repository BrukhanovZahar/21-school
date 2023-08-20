#!/bin/bash

# Проверяем, переданы ли все необходимые аргументы
if [ $# -ne 3 ]; then
    echo "Использование: $0 <путь_к_файлу_от_корня> <строка_для_замены> <замена>"
    exit 1
fi

file_path=$1           # Путь к файлу относительно корневой директории
string_to_replace=$2   # Строка, которую нужно заменить
replacement=$3         # Замена

# Выполняем замену строки в файле
sed -i "" "s/$string_to_replace/$replacement/g" "$file_path"

echo "Замена выполнена в файле: $file_path"
#full_file_path="${PWD}/${file_path}"
#file_size=$(wc -c < "$file_path")
file_size=$(stat -f%z < "$file_path")
current_date=$(date "+%Y-%m-%d %H:%M")
sha256=$(shasum -a 256 < "$file_path")
file="files.log"
echo $file_path '-' $file_size '-' $current_date '-' $sha256 'sha256' >> "$file"
