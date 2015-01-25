string Famicom = R"(

database revision=2012-10-22

release
  cartridge region=NTSC
    board type=HVC-TLSROM
    chip type=MMC3B
    prg
      rom name=program.rom size=0x40000
    chr
      rom name=character.rom size=0x20000
  information
    title:    アルマジロ
    name:     Armadillo
    region:   JP
    revision: 1.0
    board:    HVC-TLSROM-01
    serial:   IGS-9T
    sha256:   54526dc9444c0eb4b0e5814f98b5e522bcb9881a6f2c0644fc7a21ca8c03502b
    configuration
      rom name=program.rom size=0x40000
      rom name=character.rom size=0x20000

release
  cartridge region=NTSC
    board type=NAMCOT-3401
    mirror mode=horizontal
    prg
      rom name=program.rom size=0x8000
    chr
      rom name=character.rom size=0x8000
  information
    title:    バベルの塔
    name:     Babel no Tou
    region:   JP
    revision: 1.0
    board:    3401
    serial:   NAM-NBL-3900-16
    sha256:   a9d7e89bd4ea28cfd169e32c4516ef5d059e19afb9dfa4ede8412f2373dfb0a7
    configuration
      rom name=program.rom size=0x8000
      rom name=character.rom size=0x8000

release
  cartridge region=NTSC
    board type=HVC-CNROM
      security pass=0x3
    mirror mode=horizontal
    prg
      rom name=program.rom size=0x8000
    chr
      rom name=character.rom size=0x2000
  information
    title:    B-ワイング
    name:     B-Wings
    region:   JP
    revision: 1.0
    board:    HVC-CNROM-256K-01
    serial:   DFC-BW
    sha256:   2b4ac20082e2f45a8f8fd4922a0e995829719a523e118a9eec891c3206adf25b
    configuration
      rom name=program.rom size=0x8000
      rom name=character.rom size=0x2000

release
  cartridge region=NTSC
    board type=HVC-CNROM
      security pass=0x3
    mirror mode=vertical
    prg
      rom name=program.rom size=0x4000
    chr
      rom name=character.rom size=0x2000
  information
    title:    バード・ウィーク
    name:     Bird Week
    region:   JP
    revision: 1.0
    board:    HVC-CNROM-256K-01
    serial:   TFS-BK
    sha256:   acf054b0886a2ca74a0280fc36bc1d55e9845acc29759f1893c1da4c1389f9c2
    configuration
      rom name=program.rom size=0x4000
      rom name=character.rom size=0x2000

release
  cartridge region=NTSC
    board type=KONAMI-VRC-2
    chip type=VRC2
      pinout a0=0 a1=1
    prg
      rom name=program.rom size=0x20000
    chr
      rom name=character.rom size=0x20000
  information
    title:    コントラ 魂斗羅
    name:     Contra
    region:   JP
    revision: 1.0
    board:    LROG009-00
    serial:   KON-RC826
    sha256:   62c9d4e0578cb1e615ce9bb2c8ebc15b1e8de4c928c5c07ba9a85c11aa36ae4d
    configuration
      rom name=program.rom size=0x20000
      rom name=character.rom size=0x20000

release
  cartridge region=NTSC
    board type=HVC-UNROM
    chip type=74HC08
    mirror mode=horizontal
    prg
      rom name=program.rom size=0x20000
    chr
      ram size=0x2000
  information
    title:    クレイジークライマー
    name:     Crazy Climber
    region:   JP
    revision: 1.0
    board:    HVC-UNROM-02
    serial:   NBF-CY (04)
    sha256:   e24d3c754dce20e27046afeacb2dfc217950d4be766ded80c20283392cb3891e
    configuration
      rom name=program.rom size=0x20000
      ram name=character.ram size=0x2000

release
  cartridge region=NTSC
    board type=NAMCOT-3453
    chip type=118
    prg
      rom name=program.rom size=0x20000
    chr
      rom name=character.rom size=0x20000
  information
    title:    デビルマン
    name:     Devil Man
    region:   JP
    revision: 1.0
    board:    UNK-NAMCOT-DM
    serial:   NAM-DM-5500
    sha256:   d2140fc2e6354a9f4d0154dabac757e5559890edba4885799c1c979d8b7a8b20
    configuration
      rom name=program.rom size=0x20000
      rom name=character.rom size=0x20000

release
  cartridge region=NTSC
    board type=HVC-HROM
    prg
      rom name=program.rom size=0x4000
    chr
      rom name=character.rom size=0x2000
  information
    title:    ドンキーコングJr
    name:     Donkey Kong Jr.
    region:   JP
    revision: 1.0
    board:    HVC-HROM-01
    serial:   HVC-JR
    sha256:   950ebe68e7f74219b9e5e104200b03165d59c24264f02e32c12be967fd311ac2
    configuration
      rom name=program.rom size=0x4000
      rom name=character.rom size=0x2000

release
  cartridge region=NTSC
    board type=HVC-RROM
    mirror mode=vertical
    prg
      rom name=program.rom size=0x4000
    chr
      rom name=character.rom size=0x2000
  information
    title:    ダックハント
    name:     Duck Hunt
    region:   JP
    revision: 1.0
    board:    HVC-RROM-05
    serial:   HVC-DH
    sha256:   7026334a7e8742b61b450f4b3b182922c6a69fc723d7cd19c83db365f15e45ba
    configuration
      rom name=program.rom size=0x4000
      rom name=character.rom size=0x2000

release
  cartridge region=NTSC
    board type=FDS
    prg
      rom name=program.rom size=0x2000
      ram size=0x8000
    chr
      ram size=0x2000
  information
    title:    Famicom Disk System
    name:     Famicom Disk System
    region:   JP
    revision: 1.0
    board:    Famicom Disk System
    serial:   N/A
    sha256:   99c18490ed9002d9c6d999b9d8d15be5c051bdfa7cc7e73318053c9a994b0178
    configuration
      rom name=program.rom size=0x2000
      ram name=work.ram size=0x8000
      ram name=character.ram size=0x2000

release
  cartridge region=NTSC
    board type=BANDAI-JUMP2
    chip type=LZ93D50
    prg
      rom name=program.rom size=0x80000
      ram name=save.ram size=0x2000
    chr
      ram size=0x2000
  information
    title:    ファミコンジャンプII 最強の7人
    name:     Famicom Jump II - Saikyou no 7 Nin
    region:   JP
    revision: 1.0
    board:    BA-JUMP2
    serial:   BA-FJ2
    sha256:   dd031b72924e1d080f8758412c73224a274ae5e5a50d90310d578975df74101f
    configuration
      rom name=program.rom size=0x80000
      ram name=save.ram size=0x2000
      ram name=character.ram size=0x2000

release
  cartridge region=NTSC
    board type=NAMCOT-3301
    mirror mode=horizontal
    prg
      rom name=program.rom size=0x4000
    chr
      rom name=character.rom size=0x2000
  information
    title:    ギャラガ
    name:     Galaga
    region:   JP
    revision: 1.0
    board:    3301
    serial:   NAM-NGG-4500-05
    sha256:   e6fe68b9f12578e74ba016ca146aaf8232b20475fb675c7d32e0ea4e47eb1cc8
    configuration
      rom name=program.rom size=0x4000
      rom name=character.rom size=0x2000

release
  cartridge region=NTSC
    board type=NAMCOT-3301
    mirror mode=horizontal
    prg
      rom name=program.rom size=0x2000
    chr
      rom name=character.rom size=0x2000
  information
    title:    ギャラクシアン
    name:     Galaxian
    region:   JP
    revision: 1.0
    board:    3301
    serial:   NAM-NGX-4500-01
    sha256:   50178a2856f8ed3574b4e7fd45b9d1ec44c660d51fe9783d0012a19df5892cce
    configuration
      rom name=program.rom size=0x2000
      rom name=character.rom size=0x2000

release
  cartridge region=NTSC
    board type=SUNSOFT-5B
    chip type=Sunsoft-5B
    prg
      rom name=program.rom size=0x40000
    chr
      rom name=character.rom size=0x20000
  information
    title:    ギミック!
    name:     Gimmick!
    region:   JP
    revision: 1.0
    board:    FC-GMK
    serial:   SUN-GMK-6200
    sha256:   1bbe4b3e20a004a4f741018e31e6ae291772b8876d6fb6f01494c9c5b0917c6c
    configuration
      rom name=program.rom size=0x40000
      rom name=character.rom size=0x20000

release
  cartridge region=NTSC
    board type=HVC-SROM
    mirror mode=vertical
    prg
      rom name=program.rom size=0x4000
    chr
      rom name=character.rom size=0x2000
  information
    title:    ホーガンズアレイ
    name:     Hogan's Alley
    region:   JP
    revision: 1.0
    board:    HVC-SROM-03
    serial:   HVC-HA
    sha256:   8e4a04076b6a728a7e65a09737776dcb9defed7922bf0437d9a89bbe8c724b55
    configuration
      rom name=program.rom size=0x4000
      rom name=character.rom size=0x2000

release
  cartridge region=NTSC
    board type=HVC-TLROM
    chip type=MMC3C
    prg
      rom name=program.rom size=0x20000
    chr
      rom name=character.rom size=0x20000
  information
    title:    熱血格闘伝説
    name:     Nekketsu Kakutou Densetsu
    region:   JP
    revision: 1.0
    board:    HVC-TLROM-04
    serial:   TJC-NA
    sha256:   3c419e3ecf328c03364afbcf5bd15bf0029a525db9e8f74379ae1cce4062b3c3
    configuration
      rom name=program.rom size=0x20000
      rom name=character.rom size=0x20000

release
  cartridge region=NTSC
    board type=NAMCOT-3416
    chip type=118
    mirror mode=vertical
    prg
      rom name=program.rom size=0x20000
    chr
      rom name=character.rom size=0x10000
  information
    title:    カイの冒険: The Quest of Ki
    name:     Quest of Ki, The
    region:   JP
    revision: 1.0
    serial:   NAM-QK-3900
    sha256:   67123fe28cf5fbadeafc77400a0812f0135ab36706ec7d1267f84931d044e71d
    configuration
      rom name=program.rom size=0x20000
      rom name=character.rom size=0x10000

release
  cartridge region=NTSC
    board type=HVC-CNROM
      security pass=0x1
    mirror mode=vertical
    prg
      rom name=program.rom size=0x8000
    chr
      rom name=character.rom size=0x2000
  information
    title:    スパイVSスパイ
    name:     Spy vs. Spy
    region:   JP
    revision: 1.0
    board:    HVC-CNROM-256K-01
    serial:   KSC-SP
    sha256:   a9cf92ec1a080faa195d0b3dcb48fbb5ee3362f0f2f14e14e4257def48ac4346
    configuration
      rom name=program.rom size=0x8000
      rom name=character.rom size=0x2000

release
  cartridge region=NTSC
    board type=HVC-NROM-256
    mirror mode=vertical
    prg
      rom name=program.rom size=0x8000
    chr
      rom name=character.rom size=0x2000
  information
    title:    スーパーマリオブラザーズ
    name:     Super Mario Bros.
    region:   JP
    revision: 1.0
    board:    HVC-NROM-256K-02
    serial:   HVC-SM
    sha256:   fcb6a0ef3a20c19b356005fbb21dc8009563b1cb5a9aaebc8e9386b4a8c5912e
    configuration
      rom name=program.rom size=0x8000
      rom name=character.rom size=0x2000

release
  cartridge region=NTSC
    board type=HVC-NROM-256
    mirror mode=horizontal
    prg
      rom name=program.rom size=0x8000
    chr
      rom name=character.rom size=0x2000
  information
    title:    テグザー
    name:     Thexder
    region:   JP
    revision: 1.0
    board:    HVC-NROM-256K-02S
    serial:   SQF-TX
    sha256:   18d41a2dc65d8afce295eaf29c391539a69d7cfe6dd32503713ae13d4495a545
    configuration
      rom name=program.rom size=0x8000
      rom name=character.rom size=0x2000

release
  cartridge region=NTSC
    board type=FDS
    prg
      rom name=program.rom size=0x2000
      ram size=0x8000
    chr
      ram size=0x2000
  information
    title:    Twin Famicom Disk System
    name:     Twin Famicom Disk System
    region:   JP
    revision: 1.0
    board:    Famicom Disk System
    serial:   N/A
    sha256:   a0a9d57cbace21bf9c85c2b85e86656317f0768d7772acc90c7411ab1dbff2bf
    configuration
      rom name=program.rom size=0x2000
      ram name=work.ram size=0x8000
      ram name=character.ram size=0x2000

release
  cartridge region=NTSC
    board type=HVC-NROM-128
    mirror mode=vertical
    prg
      rom name=program.rom size=0x4000
    chr
      rom name=character.rom size=0x2000
  information
    title:    Wild Gunman
    name:     Wild Gunman
    region:   JP
    revision: 1.1
    board:    2I
    serial:   HVC-WG
    sha256:   adff304553b64384f86f6c2b63571f43972b9d087f92359a1b9b93b54d523542
    configuration
      rom name=program.rom size=0x4000
      rom name=character.rom size=0x2000

release
  cartridge region=NTSC
    board type=NES-SGROM
    chip type=MMC1A
    prg
      rom name=program.rom size=0x40000
    chr
      ram size=0x2000
  information
    title:    Bionic Commando
    name:     Bionic Commando
    region:   NA
    revision: 1.0
    board:    NES-SGROM-03
    serial:   NES-CM-USA
    sha256:   aeb61fd5cf5a5ed73344c46a43f8a8d539f601ff57e8f56c49bc1caea4ab3d9e
    configuration
      rom name=program.rom size=0x40000
      ram name=character.ram size=0x2000

release
  cartridge region=NTSC
    board type=NES-SLROM
    chip type=MMC1B2
    prg
      rom name=program.rom size=0x20000
    chr
      rom name=character.rom size=0x20000
  information
    title:    Clash at Demonhead
    name:     Clash at Demonhead
    region:   NA
    revision: 1.0
    board:    NES-SLROM-05
    serial:   NES-B6-USA
    sha256:   cf226f0d9486103bbaa19ee124b673d47aa2b3766334b6b7587d704c03e6649e
    configuration
      rom name=program.rom size=0x20000
      rom name=character.rom size=0x20000

release
  cartridge region=NTSC
    board type=NES-CNROM
    mirror mode=vertical
    prg
      rom name=program.rom size=0x8000
    chr
      rom name=character.rom size=0x8000
  information
    title:    Cybernoid: The Fighting Machine
    name:     Cybernoid - The Fighting Machine
    region:   NA
    revision: 1.0
    serial:   NES-YN-USA
    sha256:   ad1e14d08657d99c8b70f779931f62524b4beb529090b82b368925d8b642e40c
    configuration
      rom name=program.rom size=0x8000
      rom name=character.rom size=0x8000

release
  cartridge region=NTSC
    board type=NES-BNROM
    mirror mode=horizontal
    prg
      rom name=program.rom size=0x20000
    chr
      ram size=0x2000
  information
    title:    Deadly Towers
    name:     Deadly Towers
    region:   NA
    revision: 1.0
    board:    NES-BN-ROM-01
    serial:   NES-DE-USA
    sha256:   0115356b0791cc8ddcb7d3163d6ef7aa664f3ff4e68dba561ffffb79eefcbca9
    configuration
      rom name=program.rom size=0x20000
      ram name=character.ram size=0x2000

release
  cartridge region=NTSC
    board type=NES-SNROM
    chip type=MMC1B2
    prg
      rom name=program.rom size=0x40000
      ram name=save.ram size=0x2000
    chr
      ram size=0x2000
  information
    title:    Destiny of an Emperor
    name:     Destiny of an Emperor
    region:   NA
    revision: 1.0
    serial:   NES-YZ-USA
    sha256:   6d082c801942ce6787b471428ab4c8a6acb3e21f3f38fa197f2aeb698d9a2d7e
    configuration
      rom name=program.rom size=0x40000
      ram name=save.ram size=0x2000
      ram name=character.ram size=0x2000

release
  cartridge region=NTSC
    board type=NES-NROM-128
    mirror mode=vertical
    prg
      rom name=program.rom size=0x4000
    chr
      rom name=character.rom size=0x2000
  information
    title:    Donkey Kong Jr.
    name:     Donkey Kong Jr.
    region:   NA
    revision: 1.0
    board:    NES-NROM-128-03
    serial:   NES-JR-USA
    sha256:   950ebe68e7f74219b9e5e104200b03165d59c24264f02e32c12be967fd311ac2
    configuration
      rom name=program.rom size=0x4000
      rom name=character.rom size=0x2000

release
  cartridge region=NTSC
    board type=NES-NROM-128
    mirror mode=vertical
    prg
      rom name=program.rom size=0x4000
    chr
      rom name=character.rom size=0x2000
  information
    title:    Duck Hunt
    name:     Duck Hunt
    region:   NA
    revision: 1.0
    board:    NES-NROM-128-03
    serial:   NES-DH-USA
    serial:   NES-DH-CAN
    sha256:   7026334a7e8742b61b450f4b3b182922c6a69fc723d7cd19c83db365f15e45ba
    configuration
      rom name=program.rom size=0x4000
      rom name=character.rom size=0x2000

release
  cartridge region=NTSC
    board type=NES-UNROM
    chip type=74HC32
    mirror mode=vertical
    prg
      rom name=program.rom size=0x20000
    chr
      ram size=0x2000
  information
    title:    Disney's DuckTales
    name:     DuckTales
    region:   NA
    revision: 1.0
    board:    NES-UNROM-09
    serial:   NES-UK-USA
    sha256:   8ba8baed01a9fbaf1e9ff29e0c9825db1963ac2aff211d6f1f3bcfd3839e2013
    configuration
      rom name=program.rom size=0x20000
      ram name=character.ram size=0x2000

release
  cartridge region=NTSC
    board type=NES-UNROM
    chip type=74HC32
    mirror mode=vertical
    prg
      rom name=program.rom size=0x20000
    chr
      ram size=0x2000
  information
    title:    Disney's DuckTales 2
    name:     DuckTales 2
    region:   NA
    revision: 1.0
    board:    NES-UNROM-10
    serial:   NES-DL-USA
    sha256:   54c70628739c9cfab40b8d79555e9076adae34127ef369988ca91635b4a688bf
    configuration
      rom name=program.rom size=0x20000
      ram name=character.ram size=0x2000

release
  cartridge region=NTSC
    board type=NES-GNROM
    mirror mode=vertical
    prg
      rom name=program.rom size=0x20000
    chr
      rom name=character.rom size=0x8000
  information
    title:    Gumshoe
    name:     Gumshoe
    region:   NA
    revision: 1.0
    board:    NES-GN-ROM-01
    serial:   NES-GS-USA
    sha256:   4628f32db9b826d19fe5dd8e2c45a9f70e1041f15b7b44b06dee2f01731566e8
    configuration
      rom name=program.rom size=0x20000
      rom name=character.rom size=0x8000

release
  cartridge region=NTSC
    board type=NES-TQROM
    chip type=MMC3B
    prg
      rom name=program.rom size=0x20000
    chr
      rom name=character.rom size=0x10000
      ram size=0x2000
  information
    title:    High Speed
    name:     High Speed
    region:   NA
    revision: 1.0
    serial:   NES-8H-USA
    sha256:   710e907230bbd82143286b40a56a298b25cf326697a9f07bfd8e043c1936a4b1
    configuration
      rom name=program.rom size=0x20000
      rom name=character.rom size=0x10000
      rom name=nametable.ram size=0x2000

release
  cartridge region=NTSC
    board type=NES-NROM-128
    mirror mode=vertical
    prg
      rom name=program.rom size=0x4000
    chr
      rom name=character.rom size=0x2000
  information
    title:    Hogan's Alley
    name:     Hogan's Alley
    region:   NA
    revision: 1.0
    board:    NES-NROM-128-04
    serial:   NES-HA-USA
    sha256:   8e4a04076b6a728a7e65a09737776dcb9defed7922bf0437d9a89bbe8c724b55
    configuration
      rom name=program.rom size=0x4000
      rom name=character.rom size=0x2000

release
  cartridge region=NTSC
    board type=NES-SNROM
    chip type=MMC1B2
    prg
      rom name=program.rom size=0x20000
      ram name=save.ram size=0x2000
    chr
      ram size=0x2000
  information
    title:    The Legend of Zelda
    name:     Legend of Zelda, The
    region:   NA
    revision: 1.1
    serial:   NES-ZL-USA
    serial:   ec0d4ebf6d2fcecd1d95fef7329954efe79676959bc281ea908b226459bc6dc2
    configuration
      rom name=program.rom size=0x20000
      ram name=save.ram size=0x2000
      ram name=character.ram size=0x2000

release
  cartridge region=NTSC
    board type=NES-TLROM
    chip type=MMC3C
    prg
      rom name=program.rom size=0x40000
    chr
      rom name=character.rom size=0x20000
  information
    title:    Little Samson
    name:     Little Samson
    region:   NA
    revision: 1.0
    board:    NES-TLROM-03
    serial:   NES-LT-USA
    sha256:   a5165565263eaf8bdc45a8e6a615704f9bf271cd6d547d22c098c80cbaffd879
    configuration
      rom name=program.rom size=0x40000
      rom name=character.rom size=0x20000

release
  cartridge region=NTSC
    board type=NES-SGROM
    chip type=MMC1B2
    prg
      rom name=program.rom size=0x40000
    chr
      ram size=0x2000
  information
    title:    Mega Man 2
    name:     Mega Man 2
    region:   NA
    revision: 1.0
    sha256:   1e588d435e75d80c5c0b578b4fa8d196f2cf4346c11c9a7b7e435d768828ad01
    configuration
      rom name=program.rom size=0x40000
      ram name=character.ram size=0x2000

release
  cartridge region=NTSC
    board type=NES-TQROM
    chip type=MMC3A
    prg
      rom name=program.rom size=0x20000
    chr
      rom name=character.rom size=0x10000
      ram size=0x2000
  information
    title:    Pin-Bot
    name:     Pin-Bot
    region:   NA
    revision: 1.0
    serial:   NES-IO-USA
    sha256:   f4ddb0f1a02f823ebed30b55547344de3c8fb9d87254ff993584373ecadd9141
    configuration
      rom name=program.rom size=0x20000
      rom name=character.rom size=0x10000
      rom name=nametable.ram size=0x2000

release
  cartridge region=NTSC
    board type=NES-CNROM
    mirror mode=horizontal
    prg
      rom name=program.rom size=0x8000
    chr
      rom name=character.rom size=0x8000
  information
    title:    Puzznic
    name:     Puzznic
    region:   NA
    revision: 1.0
    board:    NES-CNROM-07
    serial:   NES-ZP-USA
    sha256:   0cf2fc17a59a0932ce43e6b2e9ea4e2570f03139784b5c9df429a499e734b92e
    configuration
      rom name=program.rom size=0x8000
      rom name=character.rom size=0x8000

release
  cartridge region=NTSC
    board type=NES-HKROM
    chip type=MMC6B
    prg
      rom name=program.rom size=0x40000
      ram name=save.ram size=0x400
    chr
      rom name=character.rom size=0x40000
  information
    title:    StarTropics
    name:     StarTropics
    region:   NA
    revision: 1.0
    serial:   NES-OC-USA
    sha256:   69de2c7552fa81ca5921da0e457abf1be35f18ffbad159788a76141be59c9f6b
    configuration
      rom name=program.rom size=0x40000
      ram name=save.ram size=0x400
      rom name=character.rom size=0x40000

release
  cartridge region=NTSC
    board type=NES-NROM-256
    mirror mode=vertical
    prg
      rom name=program.rom size=0x8000
    chr
      rom name=character.rom size=0x2000
  information
    title:    Super Mario Bros.
    name:     Super Mario Bros.
    region:   NA
    revision: 1.0
    board:    NES-NROM-256-04
    serial:   NES-SM-USA
    sha256:   fcb6a0ef3a20c19b356005fbb21dc8009563b1cb5a9aaebc8e9386b4a8c5912e
    configuration
      rom name=program.rom size=0x8000
      rom name=character.rom size=0x2000

release
  cartridge region=NTSC
    board type=NES-MHROM
    mirror mode=vertical
    prg
      rom name=program.rom size=0x10000
    chr
      rom name=character.rom size=0x4000
  information
    title:    Super Mario Bros. / Duck Hunt
    name:     Super Mario Bros. + Duck Hunt
    region:   NA
    revision: 1.0
    board:    NES-MHROM-04
    serial:   NES-MH-USA
    sha256:   5dde385041aa7364c78205f2ba49615f416c701b6025e38aa1d7b9c4f99a62db
    configuration
      rom name=program.rom size=0x10000
      rom name=character.rom size=0x4000

release
  cartridge region=NTSC
    board type=NES-TSROM
    chip type=MMC3B
    prg
      rom name=program.rom size=0x20000
      ram size=0x2000
    chr
      rom name=character.rom size=0x20000
  information
    title:    Super Mario Bros. 2
    name:     Super Mario Bros. 2
    region:   NA
    revision: 1.1
    board:    NES-TSROM-08
    serial:   NES-MW-USA
    serial:   NES-MW-CAN
    sha256:   728d0ca6751b0c039fc3e34f2e7f27a870afcab30f5e270244ac40979c5f69ca
    configuration
      rom name=program.rom size=0x20000
      ram name=work.ram size=0x2000
      rom name=character.rom size=0x20000

release
  cartridge region=NTSC
    board type=NES-TSROM
    chip type=MMC3B
    prg
      rom name=program.rom size=0x40000
      ram size=0x2000
    chr
      rom name=character.rom size=0x20000
  information
    title:    Super Mario Bros. 3
    name:     Super Mario Bros. 3
    region:   NA
    revision: 1.0
    board:    NES-TSROM-06
    serial:   NES-UM-USA
    sha256:   d77d17d34af24871d7ce1160ccd3330555835c8e940b7100e095ac38973d927a
    configuration
      rom name=program.rom size=0x40000
      ram name=work.ram size=0x2000
      rom name=character.rom size=0x20000

release
  cartridge region=NTSC
    board type=NES-TSROM
    chip type=MMC3B
    prg
      rom name=program.rom size=0x40000
      ram size=0x2000
    chr
      rom name=character.rom size=0x20000
  information
    title:    Super Mario Bros. 3
    name:     Super Mario Bros. 3
    region:   NA
    revision: 1.1
    board:    NES-TSROM-07
    serial:   NES-UM-USA
    serial:   NES-UM-CAN
    sha256:   959fdd32c71735d6fb2bd16a646d39f4ee65623273dd035e6a968e991bd13ef8
    configuration
      rom name=program.rom size=0x40000
      ram name=work.ram size=0x2000
      rom name=character.rom size=0x20000

release
  cartridge region=NTSC
    board type=NES-SEROM
    chip type=MMC1B2
    prg
      rom name=program.rom size=0x8000
    chr
      rom name=character.rom size=0x4000
  information
    title:    Tetris
    name:     Tetris
    region:   NA
    revision: 1.0
    board:    NES-SEROM-04
    serial:   NES-EI-USA
    serial:   NES-EI-CAN
    sha256:   2ae5fb18a1bf841077e3872ba05060f030ea0bfc573994b2f8fe2fb570dc7853
    configuration
      rom name=program.rom size=0x8000
      rom name=character.rom size=0x4000

release
  cartridge region=NTSC
    board type=NES-TKROM
    chip type=MMC3C
    prg
      rom name=program.rom size=0x40000
      ram name=save.ram size=0x2000
    chr
      rom name=character.rom size=0x40000
  information
    title:    Wario's Woods
    name:     Wario's Woods
    region:   NA
    revision: 1.0
    board:    NES-TKROM-10
    serial:   NES-WB-USA
    sha256:   c12771e8155b030eff0081bfabd98e57a162d6592899f29dd16f141f0e6e08a3
    configuration
      rom name=program.rom size=0x40000
      ram name=save.ram size=0x2000
      rom name=character.rom size=0x40000

release
  cartridge region=NTSC
    board type=NES-NROM-128
    mirror mode=vertical
    prg
      rom name=program.rom size=0x4000
    chr
      rom name=character.rom size=0x2000
  information
    title:    Wild Gunman
    name:     Wild Gunman
    region:   NA
    revision: 1.0
    board:    NES-NROM-128-01
    serial:   NES-WG-USA
    sha256:   62aec65696ecf24a487b7cdd19bad5cbd19f4229a89a7888634d468c67da378a
    configuration
      rom name=program.rom size=0x4000
      rom name=character.rom size=0x2000

release
  cartridge region=NTSC
    board type=NES-NROM-128
    mirror mode=vertical
    prg
      rom name=program.rom size=0x4000
    chr
      rom name=character.rom size=0x2000
  information
    title:    Wild Gunman
    name:     Wild Gunman
    region:   NA
    revision: 1.1
    board:    NES-NROM-128-04
    serial:   NES-WG-USA
    sha256:   adff304553b64384f86f6c2b63571f43972b9d087f92359a1b9b93b54d523542
    configuration
      rom name=program.rom size=0x4000
      rom name=character.rom size=0x2000

release
  cartridge region=NTSC
    board type=NES-CNROM
    mirror mode=horizontal
    prg
      rom name=program.rom size=0x8000
    chr
      rom name=character.rom size=0x8000
  information
    title:    World Class Track Meet
    name:     World Class Track Meet
    region:   NA
    revision: 1.1
    serial:   NES-WT-USA
    sha256:   ac766a8d99bfd8e95c02b9a9c68279c72ba5b3307b78edc67b52781ed185fa89
    configuration
      rom name=program.rom size=0x8000
      rom name=character.rom size=0x8000

release
  cartridge region=NTSC
    board type=NES-HKROM
    chip type=MMC6B
    prg
      rom name=program.rom size=0x40000
      ram name=save.ram size=0x400
    chr
      rom name=character.rom size=0x40000
  information
    title:    Zoda's Revenge: StarTropics 2
    name:     Zoda's Revenge - StarTropics 2
    region:   NA
    revision: 1.0
    board:    NES-HKROM-02
    serial:   NES-6C-USA
    sha256:   d0850075065ecbd125a33accc952de5d012527be45aa14a1b8223a9adf1643ae
    configuration
      rom name=program.rom size=0x40000
      ram name=save.ram size=0x400
      rom name=character.rom size=0x40000

release
  cartridge region=PAL
    board type=NES-NROM-128
    mirror mode=vertical
    prg
      rom name=program.rom size=0x4000
    chr
      rom name=character.rom size=0x2000
  information
    title:    Hogan's Alley
    name:     Hogan's Alley
    region:   EU
    revision: 1.0
    board:    NES-NROM-128-03
    serial:   NES-HA-EEC
    sha256:   8e4a04076b6a728a7e65a09737776dcb9defed7922bf0437d9a89bbe8c724b55
    configuration
      rom name=program.rom size=0x4000
      rom name=character.rom size=0x2000

release
  cartridge region=PAL
    board type=NES-TSROM
    chip type=MMC3C
    prg
      rom name=program.rom size=0x20000
      ram size=0x2000
    chr
      rom name=character.rom size=0x20000
  information
    title:    Noah's Ark
    name:     Noah's Ark
    region:   EU
    revision: 1.0
    serial:   NES-NH-NOE
    sha256:   6157c99fe7a214025c65fd3649e4afe9cd2d38c333e65af028b935e49fbeb500
    configuration
      rom name=program.rom size=0x20000
      ram name=work.ram size=0x2000
      rom name=character.rom size=0x20000

release
  cartridge region=PAL
    board type=NES-TKROM
    chip type=MMC3C
    prg
      rom name=program.rom size=0x40000
      ram name=save.ram size=0x2000
    chr
      rom name=character.rom size=0x40000
  information
    title:    Wario's Woods
    name:     Wario's Woods
    region:   EU
    revision: 1.0
    board:    NES-TKROM-10
    serial:   NES-WB-NOE
    sha256:   9fe815d8fd175ef9ef03fb010638f2b6b7aa9d11d5a40eda2476450918543e6f
    configuration
      rom name=program.rom size=0x40000
      ram name=save.ram size=0x2000
      rom name=character.rom size=0x40000

)";
