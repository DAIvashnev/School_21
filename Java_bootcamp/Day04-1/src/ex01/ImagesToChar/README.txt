Compilation:

    javac -sourcepath ./ImagesToChar/src/java/ -d ImagesToChar/target ImagesToChar/src/java/edu/school21/printer/app/Program.java

Copy resources:

    cp -r ImagesToChar/src/resources ImagesToChar/target

For creating jar-archive:

    jar cvfm ImagesToChar/target/images-to-chars-printer.jar ImagesToChar/src/manifest.txt -C ImagesToChar/target/ . -C ImagesToChar/src/resources/ .

Start program:

    java -jar ImagesToChar/target/images-to-chars-printer.jar