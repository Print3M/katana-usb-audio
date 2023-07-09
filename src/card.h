#pragma once
#include <linux/init.h>
#include <linux/module.h>
#include <sound/core.h>

int katana_new_card(struct device *dev, struct snd_card *card);