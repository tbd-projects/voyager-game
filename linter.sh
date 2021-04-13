cppcheck -I./include/  --inconclusive --enable=all --language=c --check-config \
--suppress=missingInclude -UCOUNT_PROCESSES ./src/*.c ./lib/* ./test/*.cpp
