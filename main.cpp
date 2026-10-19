#include <iostream>
#include <random>
#include <string>
#include <vector>
using namespace std;
wstring inFile, outFile;
double strength = -1;
bool Parse(int argc, wchar_t* argv[]) {
	for (int i = 1; i < argc; i++) {
		wstring t = argv[i];
		if (t == L"-i" && i + 1 < argc) inFile = argv[++i];
		else if (t == L"-o" && i + 1 < argc) outFile = argv[++i];
		else if (t == L"-s" && i + 1 < argc) {
			try { strength = stod(argv[++i]); } catch (...) { return false; }
		}
		else return false;
	}
	if (inFile.empty() || outFile.empty()) return false;
	if (strength < 0 || strength > 1) return false;
	if (_wcsicmp(inFile.c_str(), outFile.c_str()) == 0) return false;
	return true;
}

int wmain(int argc, wchar_t* argv[]) {
	ios::sync_with_stdio(false);
	if (!Parse(argc, argv)) { cout << "Fail BADARGS\n"; return 1; }
	FILE* fin = _wfopen(inFile.c_str(), L"rb");
	if (!fin) { cout << "Fail NOINPUT\n"; return 1; }
	FILE* fout = _wfopen(outFile.c_str(), L"wb");
	if (!fout) { fclose(fin); cout << "Fail NOOUTPUT\n"; return 1; }
	mt19937_64 gen(random_device{}());
	uniform_real_distribution<double> dist(0.0, 1.0);
	const int SZ = 65536;
	vector<unsigned char> buf(SZ);
	size_t n;
	bool ok = true;
	while ((n = fread(buf.data(), 1, SZ, fin)) > 0) {
		for (size_t i = 0; i < n; i++) {
			unsigned char b = buf[i];
			for (int bit = 0; bit < 8; bit++)
				if (dist(gen) < strength) b ^= (1u << bit);
			buf[i] = b;
		}
		if (fwrite(buf.data(), 1, n, fout) != n) { ok = false; break; }
	}
	if (ok && ferror(fin)) ok = false;
	fclose(fin);
	fclose(fout);
	if (!ok) { cout << "Fail IOFAIL\n"; return 1; }
	cout << "Success\n";
	return 0;
}
