GID := $(shell id -g)
UID := $(shell id -u)

DOCKER_COMPOSE = docker compose -f docker/docker-compose.yaml

export GID
export UID

up:
	@${DOCKER_COMPOSE} up -d && ${DOCKER_COMPOSE} logs -f
down:
	${DOCKER_COMPOSE} down --remove-orphans