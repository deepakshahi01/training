FROM gcc AS builder
LABEL maintainer shahideep0901@gmail.com
WORKDIR /app
COPY . .
RUN make server
FROM scratch
COPY --from=builder /app/server /
EXPOSE 8050
CMD ["./server"]
