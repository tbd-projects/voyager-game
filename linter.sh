SOURCES_DIRS=".libs ./src"
for path in ./libs/*/*/
do
  SOURCES_DIRS="${SOURCES_DIRS} ${path}"
done

cpplint --filter="-legal/copyright, -runtime/arrays, -build/include_subdir, -runtime/references, -whitespace/indent,
                                                    -build/include_what_you_use, -build/header_guard" \
                                                    --repository=./ --root=./  --recursive $SOURCES_DIRS
cppcheck $SOURCES_DIRS
