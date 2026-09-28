
#Stage 1: Build
FROM gcc:13 AS builder

WORKDIR /app

# Copy source tree
COPY include/ include/
COPY src/     src/
COPY Makefile .

# Compile
RUN make all

#Stage 2: Debug
# Built on top of the builder so the -g binary and sources are present.
# Not started by `docker compose up`; used via the "debug" compose profile.
FROM builder AS debug

RUN apt-get update \
    && apt-get install -y --no-install-recommends valgrind gdb \
    && rm -rf /var/lib/apt/lists/*

CMD ["bash"]

# Stage 3: Runtime
FROM debian:bookworm-slim AS runtime

WORKDIR /app

# Copy only the compiled binary from the builder stage
COPY --from=builder /app/campusguard ./campusguard

# Binary is the entry point; no extra arguments needed
ENTRYPOINT ["./campusguard"]
