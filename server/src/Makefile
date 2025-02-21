JAVAC = javac
JAVA_FILES = $(wildcard *.java)
CLASS_FILES = $(JAVA_FILES:.java=.class)

all: $(CLASS_FILES)

%.class: %.java
	$(JAVAC) $<

clean:
	rm -f *.class
