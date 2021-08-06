<?php
defined('BASEPATH') or exit('No direct script access allowed');
class prosestimbang extends CI_Controller
{
    public function index()
    {
        if (isset($_POST['DataStr'])) {
            $data = $this->db->get_where('timbang', ['id' => 1])->row_array();
            echo $data['status'];
            $nilai = htmlspecialchars($this->input->post('DataStr', true));
            $this->db->set('nilai', $nilai);
            $this->db->where('id', 1);
            $this->db->update('timbang');
            $this->db->set('status', $nilai);
            $this->db->where('id', 2);
            $this->db->update('timbang');
        } elseif (isset($_POST['DataStr1'])) {
            $data = $this->db->get_where('timbang', ['id' => 1])->row_array();
            echo $data['status'];
            $nilai = htmlspecialchars($this->input->post('DataStr1', true));
            $this->db->set('jam', date('H:i:s'));
            $this->db->set('nilai', $nilai);
            $this->db->where('id', 2);
            $this->db->update('timbang');
            $this->db->set('status', $nilai);
            $this->db->where('id', 2);
            $this->db->update('timbang');
        } elseif (isset($_POST['Cek'])) {
            $data = $this->db->get_where('timbang', ['id' => 1])->row_array();
            echo $data['status'];
        } elseif (isset($_POST['TT1'])) {
            $this->db->set('jam', date('H:i:s'));
            $this->db->set('status', "T1");
            $this->db->where('id', 1);
            $this->db->update('timbang');
        } elseif (isset($_POST['TT2'])) {
            $this->db->set('status', "T2");
            $this->db->where('id', 1);
            $this->db->update('timbang');
            $this->db->set('jam', date('H:i:s'));
            $this->db->set('status', 0);
            $this->db->where('id', 2);
            $this->db->update('timbang');
        } elseif (isset($_POST['SLS'])) {
            $this->db->set('status', "SLS");
            $this->db->where('id', 1);
            $this->db->update('timbang');

            $data1 = $this->db->get_where('timbang', ['id' => 1])->row_array();
            $data2 = $this->db->get_where('timbang', ['id' => 2])->row_array();
            $datatimbang = [
                'tanggal' => tanggal() . date('H:i:s'),
                'tim1' => $data1['nilai'],
                'jam1' => $data1['jam'],
                'tim2' => $data2['nilai'],
                'jam2' => $data2['jam'],
                'jumlah_muatan_ton' => $data1['total']
            ];
            $this->db->update('penjualan', $datatimbang);
            $data = $this->db->get_where('penjualan', ['id' => 1])->row_array();
            if ($data['kubik'] > 0) {
                $data3 = $this->db->get_where('databarang', ['id_barang' => $data['id_barang']])->row_array();
                if ($data['jn_penjualan'] == "do") {
                    $pindah = [
                        'tanggal' => tanggal() . ("\n") . date('H:i:s'),
                        'nama_do' => $data['nama_do'],
                        'perusahaan' => $data['perusahaan'],
                        'id_transaksi' => $data['id_transaksi'],
                        'id_pesanan' => $data['id_pesanan'],
                        'id_pelanggan' => $data['id_pelanggan'],
                        'nama_do' => $data['nama_do'],
                        'perusahaan' => $data['perusahaan'],
                        'jenis_mobil' => $data['jenis_mobil'],
                        'nopol' => $data['nopol'],
                        'nama_sopir' => $data['nama_sopir'],
                        'alamat' => $data['alamat'],
                        'telp' => $data['telp'],
                        'id_barang' => $data['id_barang'],
                        'jenis_batu' => $data['jenis_batu'],
                        'tim1' => $data['tim1'],
                        'tim2' => $data['tim2'],
                        'jumlah_muatan_ton' => $data['jumlah_muatan_ton'],
                        'kubik' => $data['kubik']
                    ];
                    $this->db->insert('penjualan_do', $pindah);
                    $this->db->select_sum('kubik');
                    $data4['jumlah'] = $this->db->get_where('penjualan_do', ['id_pesanan' => $data['id_pesanan']])->row()->kubik;
                    $data6 = $this->db->get_where('pesanando', ['id_pesanan' => $data['id_pesanan']])->row_array();
                    $data5['sisaorder'] = $data6['jumlah_pesanan'] - $data4['jumlah'];

                    $this->db->set('diambil', $data4['jumlah']);
                    $this->db->set('sisa_pesanan', $data5['sisaorder']);
                    $this->db->where('id_pesanan', $data['id_pesanan']);
                    $this->db->update('pesanando');
                } elseif ($data['jn_penjualan'] == "kontan") {
                    $pindah = [
                        'tanggal' => tanggal() . ("\n") . date('H:i:s'),
                        'nama' => $data['nama_do'],
                        'id_transaksi' => $data['id_transaksi'],
                        'jenis_mobil' => $data['jenis_mobil'],
                        'nopol' => $data['nopol'],
                        'nama_sopir' => $data['nama_sopir'],
                        'alamat' => $data['alamat'],
                        'telp' => $data['telp'],
                        'id_barang' => $data['id_barang'],
                        'jenis_batu' => $data['jenis_batu'],
                        'ukuran' => $data3['ukuran'],
                        'tim1' => $data['tim1'],
                        'tim2' => $data['tim2'],
                        'jumlah_muatan_ton' => $data['jumlah_muatan_ton'],
                        'kubik' => $data['kubik'],
                        'bayar' => $data['bayar']
                    ];
                    $this->db->insert('penjualan_kontan', $pindah);
                }
                $this->db->select_sum('kubik');
                $data7['jumlah_do'] = $this->db->get_where('penjualan_do', ['id_pesanan' => $data['id_pesanan']])->row()->kubik;
                $this->db->select_sum('kubik');
                $data7['jumlah_kontan'] = $this->db->get_where('penjualan_kontan', ['id_transaksi' => $data['id_transaksi']])->row()->kubik;
                $data7['jumlah_total'] = $data7['jumlah_do'] + $data7['jumlah_kontan'];

                $data6 = $this->db->get_where('databarang', ['id_barang' => $data['id_barang']])->row_array();
                $data7['sisa_stok'] = $data6['stok_barang'] - $data7['jumlah_total'];

                $this->db->set('sisa_stok', $data7['sisa_stok']);
                $this->db->where('id_barang', $data['id_barang']);
                $this->db->update('databarang');
            }
        } elseif (isset($_POST['NOTA'])) {
            redirect('prosestimbang/cetaknota');
        } elseif (isset($_POST['FAKTURDO'])) {
            redirect('prosestimbang/cetakfakturdo');
        } elseif (isset($_POST['FAKTUR'])) {
            redirect('prosestimbang/cetakfaktur');
        } else {
            $kosong = [
                'tanggal' => "",
                'id_pesanan' => "",
                'id_pelanggan' => "",
                'jn_penjualan' => "do",
                'nama_do' => "",
                'perusahaan' => "",
                'id_transaksi' => "",
                'jenis_mobil' => "",
                'nopol' => "",
                'nama_sopir' => "",
                'alamat' => "",
                'telp' => "",
                'id_barang' => "",
                'jenis_batu' => "",
                'ukuran' => "",
                'tim1' => "",
                'jam1' => "",
                'tim2' => "",
                'jam2' => "",
                'jumlah_muatan_ton' => "",
                'kubik' => 0,
                'bayar' => 0,
                'harga' => 0,
                'berat' => 0
            ];
            $this->db->update('penjualan', $kosong);

            $this->db->set('total', 0);
            $this->db->set('nilai', 0);
            $this->db->set('status', "SLS");
            $this->db->where('id', 1);
            $this->db->update('timbang');

            $this->db->set('nilai', 0);
            $this->db->set('total', 0);
            $this->db->set('status', 0);
            $this->db->where('id', 2);
            $this->db->update('timbang');
        }
        redirect('menupilihan/penjualan');
    }

    public function cetaknota()
    {
        $data['akun'] = $this->db->get_where('akun', ['telp' => $this->session->userdata('telp')])->row_array();
        $data['status'] = $this->db->get_where('role_akun', ['id' => $this->session->userdata('jabatan')])->row_array();
        $data['icon'] = $this->db->get_where('role_akun', ['id' => $this->session->userdata('jabatan')])->row_array();
        $data['nota'] = $this->db->get_where('penjualan', ['id' => 1])->row_array();

        $this->load->view('templates/header_print_p', $data);
        $this->load->view('prosestimbang/cetaknota', $data);
        $this->load->view('templates/footer_print');
    }
    public function cetakfakturdo()
    {
        $data['akun'] = $this->db->get_where('akun', ['telp' => $this->session->userdata('telp')])->row_array();
        $data['status'] = $this->db->get_where('role_akun', ['id' => $this->session->userdata('jabatan')])->row_array();
        $data['icon'] = $this->db->get_where('role_akun', ['id' => $this->session->userdata('jabatan')])->row_array();
        $data['nota'] = $this->db->get_where('penjualan', ['id' => 1])->row_array();
        $data2 = $this->db->get_where('pesanando', ['id' => $this->input->post('fakturdo', true)])->row_array();


        $harga = $data2['harga'] * $data2['diambil'];
        if ($harga > $data2['jumlah_uang_muka']) {
            $sisaharga = $harga - $data2['jumlah_uang_muka'];
        } else {
            $sisaharga = 0;
        }


        $this->db->set('tagihan', $sisaharga);
        $this->db->set('id_barang', $data2['id_barang']);
        $this->db->set('harga', $data2['harga']);
        $this->db->set('ukuran', $data2['ukuran']);
        $this->db->where('id_pelanggan', $data2['id_pelanggan']);
        $this->db->update('pesanando');

        $data['faktur'] = $this->db->get_where('pesanando', ['id_pesanan' => $data2['id_pesanan']])->row_array();

        $this->load->view('templates/header_print_l', $data);
        $this->load->view('prosestimbang/cetakfakturdo', $data);
        $this->load->view('templates/footer_print');
    }
    public function cetakfaktur()
    {
        $data['akun'] = $this->db->get_where('akun', ['telp' => $this->session->userdata('telp')])->row_array();
        $data['status'] = $this->db->get_where('role_akun', ['id' => $this->session->userdata('jabatan')])->row_array();
        $data['icon'] = $this->db->get_where('role_akun', ['id' => $this->session->userdata('jabatan')])->row_array();
        $data['nota'] = $this->db->get_where('penjualan', ['id' => 1])->row_array();

        $this->load->view('templates/header_print_l', $data);
        $this->load->view('prosestimbang/cetakfaktur', $data);
        $this->load->view('templates/footer_print');
    }
}
