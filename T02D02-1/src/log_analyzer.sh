#!/bin/bash

# Проверяем, что передан аргумент с путем до файла лога
if [ $# -eq 0 ]; then
    echo "Ошибка: не указан путь до файла лога."
    exit 1
fi

# Проверяем, что файл существует
if [ ! -f "$1" ]; then
    echo "Ошибка: файл '$1' не существует."
    exit 1
fi

# Анализируем файл лога и получаем общее количество записей, уникальных файлов и количество изменений, приведших к изменению hash файла
total_entries=$(wc -l < "$1")
unique_files=$(grep -oE '/\S+' "$1" | sort -u | wc -l)
changed_hashes=$(awk '{print $8}' "$1" | sort -u | wc -l)
ans_third=$(($changed_hashes - $unique_files))

echo $total_entries $unique_files $ans_third
