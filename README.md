# Multi Shell

Multi Shell, birden fazla terminal sekmesi ile komutları çalıştırmanıza ve mesajlar göndermenize olanak tanıyan bir GTK+ tabanlı uygulamadır. Bu proje, terminal sekmeleri arasında mesaj alışverişi yapmanızı sağlar ve her terminalde komutları çalıştırabilirsiniz.

## İçindekiler

- [Projenin Amacı](#projenin-amacı)
- [Özellikler](#özellikler)
- [Kullanılan Teknolojiler](#kullanılan-teknolojiler)
- [Kurulum](#kurulum)
- [Kullanım](#kullanım)
- [Dosya Yapısı](#dosya-yapısı)
- [Katkıda Bulunma](#katkıda-bulunma)
- [Lisans](#lisans)

## Projenin Amacı

Bu projenin amacı, kullanıcıların birden fazla terminal sekmesi arasında geçiş yaparak komut çalıştırmalarına ve sekmeler arasında mesaj göndermelerine olanak tanıyan bir uygulama geliştirmektir. Bu, özellikle çoklu görevlerin yürütülmesi ve farklı terminallerde çalışmanın kolaylaştırılması için kullanışlıdır.

## Özellikler

- Birden fazla terminal sekmesi oluşturma
- Terminal sekmeleri arasında mesaj gönderme
- Her terminalde komut çalıştırma
- Kullanıcı dostu arayüz
- Renkli ve okunabilir tema
- Paylaşımlı hafıza kullanarak mesaj alışverişi

## Kullanılan Teknolojiler

- *C*: Uygulamanın ana programlama dili.
- *GTK+*: Grafiksel kullanıcı arayüzü oluşturmak için kullanılan kütüphane.
- *POSIX Semaphores ve Shared Memory*: Terminaller arası mesajlaşma ve senkronizasyon için kullanılan teknolojiler.

## Kurulum

Bu projeyi çalıştırmak için aşağıdaki adımları izleyin:

### Gereksinimler

- GTK+ 3.0
- GCC
- Make

### Adımlar

1. Depoyu klonlayın:
    sh
    git clone https://github.com/yourusername/multi-shell.git
    cd multi-shell
    

2. Gereksinimlerin yüklü olduğundan emin olun:
    sh
    sudo apt-get install libgtk-3-dev build-essential
    

3. Projeyi derleyin:
    sh
    make
    

4. Uygulamayı başlatın:
    sh
    ./shellgui
    

## Kullanım

Uygulama açıldıktan sonra aşağıdaki adımları izleyerek kullanabilirsiniz:

1. *Yeni terminal ekleme:* Terminal Ekle butonuna tıklayarak yeni bir terminal sekmesi ekleyin.
2. *Komut çalıştırma:* Terminal giriş kutusuna komutu yazın ve Enter tuşuna basarak çalıştırın.
3. *Mesaj gönderme:* Terminal giriş kutusuna @msg mesajınız formatında mesaj yazın ve Enter tuşuna basarak tüm terminallere gönderin.

## Dosya Yapısı

- main.c: Uygulamanın ana dosyası, GTK+ arayüzünü oluşturur ve yönetir.
- controller.c: Kullanıcı girdilerini işler ve model ile etkileşir.
- model.c: Paylaşımlı hafıza ve komutları çalıştırma işlemlerini yönetir.
- model.h: model.c dosyasının başlık dosyası.
- Makefile: Projeyi derlemek için kullanılan Makefile.
- style.css: GTK+ arayüzü için stil dosyası.

### Dosya Açıklamaları

#### main.c

Ana uygulama dosyasıdır. GTK+ arayüzünü oluşturur ve yönetir. Kullanıcı etkileşimlerini işler ve terminalleri yönetir.

#### controller.c

Kullanıcı girdilerini işler ve model ile etkileşir. Kullanıcının terminale yazdığı komutları alır ve model üzerinden çalıştırır veya mesajları diğer terminallere gönderir.

#### model.c

Paylaşımlı hafıza ve komutları çalıştırma işlemlerini yönetir. Komutları çalıştırır ve paylaşımlı hafıza üzerinden mesaj gönderme ve alma işlemlerini gerçekleştirir.

#### model.h

model.c dosyasının başlık dosyasıdır. model.c dosyasında kullanılan fonksiyonların prototiplerini içerir.

#### Makefile

Projeyi derlemek için kullanılan Makefile'dir. make komutu ile projeyi derlemek için kullanılır.

#### style.css

GTK+ arayüzü için stil dosyasıdır. Uygulamanın temasını ve yazı tiplerini ayarlar.

## Katkıda Bulunma

Katkıda bulunmak için:

1. Bu repoyu forklayın.
2. Yeni bir özellik dalı oluşturun (git checkout -b feature/AmazingFeature).
3. Değişikliklerinizi yapın (git commit -m 'Add some AmazingFeature').
4. Dalınıza push edin (git push origin feature/AmazingFeature).
5. Bir Pull Request açın.

## Lisans

Bu proje MIT Lisansı ile lisanslanmıştır. Daha fazla bilgi için LICENSE dosyasına bakın.
