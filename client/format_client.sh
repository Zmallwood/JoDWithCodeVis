find src -type f -name "*.cpp" | xargs uncrustify -c ./uncrustify.cfg --no-backup;
find src -type f -name "*.hpp" | xargs uncrustify -c ./uncrustify.cfg --no-backup;
