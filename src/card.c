#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <sound/core.h>

int katana_new_card(struct device *dev, struct snd_card *card)
{
	/*
	    Create a new ALSA card structure.
    */
	int err = 0;

	// Find first free index for a new ALSA card
	int idx = 0;
	while (snd_card_ref(idx) != NULL) {
		idx++;
	}

	err = snd_card_new(dev, idx, "katana-usb-audio", THIS_MODULE, 0, &card);
	if (err != 0) {
		dev_err(dev, "ALSA card creation failed: %d\n", err);
		return -1;
	}

	// Basic info about the new sound card
	strcpy(card->driver, "katana_audio");
	strcpy(card->shortname, "Katana Audio");
	strcpy(card->longname, "SoundBlaster X Katana");
	card->dev = dev;

	dev_info(dev, "New ALSA card created: %s\n", card->longname);

	err = snd_card_register(card);
	if (err != 0) {
		dev_err(dev, "ALSA card registration failed: %d\n", err);
		snd_card_free(card);
		return -1;
	}

	dev_info(dev, "New ALSA card registered: %s\n", card->longname);

	return 0;
}