# Use a very small Linux base
FROM alpine
# Print a message when the container runs
CMD ["echo", "Hello! This image was built and pushed by Jenkins!"]
