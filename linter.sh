
SOURCES_DIRS=".libs ./src"
for path in ./libs/*/*/
do
  SOURCES_DIRS="${SOURCES_DIRS} ${path}"
done

cpplint --filter="-legal/copyright, -runtime/arrays, -build/include_subdir, -whitespace/indent" --repository=./ --root=./  --recursive $SOURCES_DIRS
cppcheck $SOURCES_DIRS
