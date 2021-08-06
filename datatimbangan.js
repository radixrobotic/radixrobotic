$(document).ready(function (event) {

    $('#tabelLaporan').DataTable({
        dom: 'Bfrtip',
        buttons: [
            {
                extend: 'print',
                orientation: 'landscape',
                pageSize: 'A4'
            },
            {
                extend: 'pdf',
                orientation: 'landscape',
                pageSize: 'A4'
            }
        ]
    });

    $('#cetakprint').DataTable({
        dom: 'Bfrtip',
        buttons: [
            'pdf', 'print'
        ]
    });

    $('#dataTable').DataTable();

    $('#inputan_in').on('keypress', function (event) {
        var keycode = (event.keyCode ? event.keyCode : event.which);
        if ((keycode == 13) || (keycode == 9)) {
            const id_pelanggan_in = $('#id_pelanggan_in').val();
            const nama_in = $('#nama_in').val();
            $.ajax({
                url: "cekPelanggan",
                type: 'post',
                data: {
                    id_pelanggan_in: id_pelanggan_in,
                    nama_in: nama_in
                },
                success: function () {
                    document.location.href = "order";
                }
            });
        }
    });

    $('#btn_order_do').on('click', function () {
        const cek_order = $(this).data('btn_order_do');
        $.ajax({
            url: "kondisiOrder",
            type: 'post',
            data: {
                btn_order_do: cek_order
            },
            success: function () {
                document.location.href = "order";
            }
        });
    });

    $('#cek_order_do').on('click', function () {
        const cek_order = $(this).data('orderdo');
        $.ajax({
            url: "cekbarulama",
            type: 'post',
            data: {
                dcek_order: cek_order
            },
            success: function () {
                document.location.href = "order";
            }
        });
    });

    $('#rkontan').on('click', function () {
        const kontan = $(this).data('kont');
        $.ajax({
            url: "radiopilihan",
            type: 'post',
            data: {
                dkontan: kontan
            },
            success: function () {
                document.location.href = "penjualan";
            }
        });
    });

    $('#rdo').on('click', function () {
        const kontan = $(this).data('do');
        $.ajax({
            url: "radiopilihan",
            type: 'post',
            data: {
                dkontan: kontan
            },
            success: function () {
                document.location.href = "penjualan";
            }
        });
    });

    $('#selectdo').change(function () {
        const idpel = $(this).val();
        $.ajax({
            url: "selectdo",
            type: 'post',
            data: {
                dselectdo: idpel
            },
            success: function () {
                document.location.href = "penjualan";
            }
        });
    });

    $('#tabelInput').on('keypress', function (event) {
        var keycode = (event.keyCode ? event.keyCode : event.which);
        if ((keycode == 13) || (keycode == 9)) {
            const namapelanggan = $('#namapelanggan').val();
            const jualtrans = $('#jualtrans').val();
            const jenmob = $('#jenmob').val();
            const nopol = $('#nopol').val();
            const namasupir = $('#namasupir').val();
            const alamatp = $('#alamatp').val();
            const telpp = $('#telpp').val();
            const jenbatu = $('#jenbatu').val();
            $.ajax({
                url: "transaksi",
                type: 'post',
                data: {
                    namapelanggan: namapelanggan,
                    jualtrans: jualtrans,
                    jenmob: jenmob,
                    nopol: nopol,
                    namasupir: namasupir,
                    alamatp: alamatp,
                    telpp: telpp,
                    jenbatu: jenbatu
                },
                success: function () {
                    document.location.href = "penjualan";
                }
            });
        }
    });

    $('#mulaitimbang').on('click', function () {
        const namapelanggan = $('#namapelanggan').val();
        const jualtrans = $('#jualtrans').val();
        const jenmob = $('#jenmob').val();
        const nopol = $('#nopol').val();
        const namasupir = $('#namasupir').val();
        const alamatp = $('#alamatp').val();
        const telpp = $('#telpp').val();
        const jenbatu = $('#jenbatu').val();
        $.ajax({
            url: "transaksi",
            type: 'post',
            data: {
                namapelanggan: namapelanggan,
                jualtrans: jualtrans,
                jenmob: jenmob,
                nopol: nopol,
                namasupir: namasupir,
                alamatp: alamatp,
                telpp: telpp,
                jenbatu: jenbatu
            },
            success: function () {
                document.location.href = "penjualan";
            }
        });
    });

    var waktuint = setInterval(function () {
        $('#timbang1').load('prosestimbang');
        $('#timbang2').load('prosestimbang1');
        $('#timbang3').load('prosestimbang2');
        $('#muatan').load('prosestimbang3');
        $('#mkubik').load('prosestimbang4');
        $('#bayaran').load('prosestimbang5');
        $('#wkt_jam').load('tampilJam');
    }, 1000);
});


