#include <sound/pcm.h>

static struct snd_pcm_hardware snd_mychip_playback_hw = {
	.info = (SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED | SNDRV_PCM_INFO_BLOCK_TRANSFER |
		 SNDRV_PCM_INFO_MMAP_VALID),
	.formats	  = SNDRV_PCM_FMTBIT_S16_LE,
	.rates		  = SNDRV_PCM_RATE_8000_48000,
	.rate_min	  = 8000,
	.rate_max	  = 48000,
	.channels_min	  = 2,
	.channels_max	  = 2,
	.buffer_bytes_max = 32768,
	.period_bytes_min = 4096,
	.period_bytes_max = 32768,
	.periods_min	  = 1,
	.periods_max	  = 1024,
};

static int snd_katana_pcm_hw_params(struct snd_pcm_substream *substream,
				    struct snd_pcm_hw_params *hw_params)
{
	return snd_pcm_lib_malloc_pages(substream, params_buffer_bytes(hw_params));
}

static int snd_katana_pcm_hw_free(struct snd_pcm_substream *substream)
{
	return snd_pcm_lib_free_pages(substream);
}

static int snd_katana_playback_open(struct snd_pcm_substream *substream)
{
	return 0;
}

static int snd_katana_playback_close(struct snd_pcm_substream *substream)
{
	return 0;
}

/*
static snd_pcm_uframes_t snd_katana_pcm_pointer(struct snd_pcm_substream *substream)
{
	struct snd_card *card = snd_pcm_substream_chip(substream);
	unsigned int current_ptr;

	// get the current hardware pointer
	current_ptr = mychip_get_hw_pointer(chip);
	return current_ptr;
}
*/

static int snd_mychip_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		/* do something to start the PCM engine */
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		/* do something to stop the PCM engine */
		break;
	default:
		return -EINVAL;
	}

	return 0;
}