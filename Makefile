# ==========[ Compiler Settings ]==========
CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
LDFLAGS = -lpthread

# ==========[ Directories ]==========
BUILD_DIR = build
SERVER_BUILD = $(BUILD_DIR)/server
CLIENT_BUILD = $(BUILD_DIR)/client

INCLUDE_DIR = include

# ==========[ Source Files ]==========
COMMON_SRC = src/common/socket_utils.c
SERVER_SRC = src/server/main.c src/server/chat_server.c
CLIENT_SRC = src/client/main.c src/client/chat_client.c

# ==========[ Build Directories ]==========
$(shell mkdir -p $(SERVER_BUILD) $(CLIENT_BUILD))

# ==========[ Targets ]==========
all: server client

# ==========[ Server ]==========
SERVER_TARGET = $(SERVER_BUILD)/chat_server
SERVER_OBJ = $(SERVER_BUILD)/socket_utils.o $(SERVER_BUILD)/main.o $(SERVER_BUILD)/chat_server.o

server: $(SERVER_TARGET)

$(SERVER_TARGET): $(SERVER_OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo "✅ Server build complete → $@"

$(SERVER_BUILD)/socket_utils.o: $(COMMON_SRC)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR)/common -I$(INCLUDE_DIR)/server -c $< -o $@

$(SERVER_BUILD)/main.o: src/server/main.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR)/common -I$(INCLUDE_DIR)/server -c $< -o $@

$(SERVER_BUILD)/chat_server.o: src/server/chat_server.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR)/common -I$(INCLUDE_DIR)/server -c $< -o $@

# ==========[ Client ]==========
CLIENT_TARGET = $(CLIENT_BUILD)/chat_client
CLIENT_OBJ = $(CLIENT_BUILD)/socket_utils.o $(CLIENT_BUILD)/main.o $(CLIENT_BUILD)/chat_client.o

client: $(CLIENT_TARGET)

$(CLIENT_TARGET): $(CLIENT_OBJ)
	$(CC) $^ -o $@ $(LDFLAGS)
	@echo "✅ Client build complete → $@"

$(CLIENT_BUILD)/socket_utils.o: $(COMMON_SRC)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR)/common -I$(INCLUDE_DIR)/client -c $< -o $@

$(CLIENT_BUILD)/main.o: src/client/main.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR)/common -I$(INCLUDE_DIR)/client -c $< -o $@

$(CLIENT_BUILD)/chat_client.o: src/client/chat_client.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR)/common -I$(INCLUDE_DIR)/client -c $< -o $@

# ==========[ Clean ]==========
clean:
	rm -rf $(BUILD_DIR)/server $(BUILD_DIR)/client
	@echo "🧹 Clean complete"

clean-server:
	rm -rf $(BUILD_DIR)/server
	@echo "🧹 Server cleaned"

clean-client:
	rm -rf $(BUILD_DIR)/client
	@echo "🧹 Client cleaned"

# ==========[ Help ]==========
help:
	@echo "Available targets:"
	@echo "  make all           - Build both server and client"
	@echo "  make server        - Build only server"
	@echo "  make client        - Build only client"
	@echo "  make clean         - Clean everything"
	@echo "  make clean-server  - Clean server only"
	@echo "  make clean-client  - Clean client only"
	@echo ""
	@echo "After build:"
	@echo "  ./build/server/chat_server"
	@echo "  ./build/client/chat_client"

.PHONY: all server client clean clean-server clean-client help