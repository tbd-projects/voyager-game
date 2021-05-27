SOURCES_DIRS=".libs ./src"
for path in ./libs/*/*/
do
  SOURCES_DIRS="${SOURCES_DIRS} ${path}"
done

cpplint --filter="-legal/copyright, -runtime/arrays, -build/include_subdir, -build/header_guard, -build/include_order, \
                                                    -whitespace/indent, -build/include_what_you_use, -runtime/references" \
                                                    --repository=./ --root=./  --recursive $SOURCES_DIRS
cppcheck $SOURCES_DIRS
