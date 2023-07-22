#launch instruction

#first, install the custom JAR (ChaseLogic) into your local Maven repository
mvn install:install-file -Dfile=${project.basedir}/src/main/resources/ChaseLogic-1.0.jar -DgroupId=org.example -DartifactId=ChaseLogic -Dversion=1.0 -Dpackaging=jar -DgeneratePom=true

#execute maven command
mvn clean package

#run program
java -jar target/game.jar --enemiesCount=10 --wallsCount=10 --size=30 --profile=production