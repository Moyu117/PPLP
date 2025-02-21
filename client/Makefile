##########################################################
# Makefile pour compiler le projet C++ / client
##########################################################

# Détection automatique du système d'exploitation
UNAME_S := $(shell uname -s)

# Compilateur et options
CXX      = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -g  # Ajout de -g pour le debug

# Ajout conditionnel de -lws2_32 pour Windows
ifeq ($(UNAME_S), Linux)
    LDFLAGS  =   # Linux 不需要额外库
else
    LDFLAGS  = -lws2_32  # Windows 需要链接 WinSock2
endif

# Liste des fichiers sources (.cpp)
SRCS = main.cpp \
       Vecteur2D.cpp \
       Segment.cpp \
       Polygone.cpp \
       Point.cpp \
       Groupe.cpp \
       Transformation.cpp \
       Translation.cpp \
       DrawTCPVisitor.cpp \
       SauvegardeTexteVisitor.cpp \
       NetworkInitializer.cpp

# Génère la liste des .o correspondants
OBJS = $(SRCS:.cpp=.o)

# Nom de l'exécutable final
TARGET = monappli

##########################################################
# Règles de compilation
##########################################################

# Règle par défaut (all)
all: $(TARGET)

# Édition de liens : regrouper tous les .o
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Règle générique pour compiler un .cpp en .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# "make clean" pour nettoyer les fichiers compilés
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
