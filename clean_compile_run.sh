rm -rf code/java/bin/*
javac -d code/java/bin $(find code/java/src -name '*.java')
java -cp code/java/bin Main
