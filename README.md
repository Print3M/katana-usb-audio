# SoundBlasterX Katana (Linux Kernel Module) audio control driver
First attempt at implementing the ALSA driver in order to finally get my SoundBlaster X Katana (USB) loudspeaker be handled properly under Linux and to learn how the Linux kernel-space drivers work. This module uses the ALSA and the USB core framework. Because of its educational purpose, there are a lot of comments in the code, which are most most probably not necessary for more experienced driver developers.

**Current state of the project**: the USB driver is attached to the Katana device successfully. It's able to create an ALSA card structure and associate a volume control structure with it. The driver is not visible in the PulseAudio control panel yet. I guess I need to create a PCM playback structure to see it there. However, the driver is visible in the `alsamixer` indeed. There is a single volume slider (I don't know what it is exactly) and that slider actually triggers ALSA control callback functions.

> NOTICE: The `.vscode` configuration can be used in any Linux-kernel-related project but the kernel's version used in paths needs to be adjusted.

## Usage

```bash
make                                # Build
sudo insmod katana-audio-control.ko # Load module
sudo lsmod | grep katana            # Check if loaded
make clean                          # Clean
sudo rmmod katana_audio_control     # Remove module
sudo dmesg                          # Read logs
```

> NOTICE: Sometimes the Linux kernel stubbornly probes the `snd-usb-audio` driver first. Manual removal of this default driver might be helpful (`rmmod snd-usb-audio`). It will be loaded anyway but most probably after probing of this custom driver. The order of drivers to probe is strange for me.

All logs can be seen using the `dmesg` command.

## Resources to write USB driver

* [O'Reilly, USB Drivers](https://www.oreilly.com/library/view/linux-device-drivers/0596005903/ch13.html)
* [Linux Kernel docs - Writing USB Device Drivers](https://docs.kernel.org/driver-api/usb/writing_usb_driver.html)
* [Linux Kernel docs - USB Host Side API](https://www.kernel.org/doc/html/latest/driver-api/usb/usb.html)
* [ALSA Driver API docs](https://www.kernel.org/doc/html/latest/sound/kernel-api/alsa-driver-api.html)
* [Writing an ALSA driver](https://www.kernel.org/doc/html/latest/sound/kernel-api/writing-an-alsa-driver.html)
