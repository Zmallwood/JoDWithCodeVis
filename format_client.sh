find src_client -type f -name "*.cpp" | xargs uncrustify -c ./uncrustify.cfg --no-backup;
find src_client -type f -name "*.hpp" | xargs uncrustify -c ./uncrustify.cfg --no-backup;
