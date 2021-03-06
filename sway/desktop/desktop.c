#include "sway/tree/container.h"
#include "sway/desktop.h"
#include "sway/output.h"

void desktop_damage_surface(struct wlr_surface *surface, double lx, double ly,
		bool whole) {
	for (int i = 0; i < root->outputs->length; ++i) {
		struct sway_output *output = root->outputs->items[i];
		output_damage_surface(output, lx - output->wlr_output->lx,
				ly - output->wlr_output->ly, surface, whole);
	}
}

void desktop_damage_whole_container(struct sway_container *con) {
	for (int i = 0; i < root->outputs->length; ++i) {
		struct sway_output *output = root->outputs->items[i];
		output_damage_whole_container(output, con);
	}
}

void desktop_damage_box(struct wlr_box *box) {
	for (int i = 0; i < root->outputs->length; ++i) {
		struct sway_output *output = root->outputs->items[i];
		output_damage_box(output, box);
	}
}

void desktop_damage_view(struct sway_view *view) {
	desktop_damage_whole_container(view->container);
	struct wlr_box box = {
		.x = view->container->current.view_x - view->geometry.x,
		.y = view->container->current.view_y - view->geometry.y,
		.width = view->surface->current.width,
		.height = view->surface->current.height,
	};
	desktop_damage_box(&box);
}
