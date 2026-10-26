#include "libtest.h"

namespace Hospitalnames {

	int Paciente::prioridadPaciente() const {
		if (enfermedades->empty()) return 0;
		int maxP = 0;
		for (const auto& e : *enfermedades) {
			int p = e.prioridad();
			if (p > maxP) maxP = p;
		}
		return maxP;
	}

	Enfermedad Paciente::tratarEnfermedad(Doctor& d) {
		if (enfermedades->empty()) return Enfermedad();
		auto it = enfermedades->begin();
		auto maxIt = it;
		int maxP = it->prioridad();
		for (; it != enfermedades->end(); ++it) {
			if (it->prioridad() > maxP) {
				maxP = it->prioridad();
				maxIt = it;
			}
		}
		Enfermedad e = *maxIt;
		enfermedades->erase(maxIt);
		historial->push(std::make_pair(e, d));
		d.addPendiente(e);
		return e;
	}

	int Hospital::pagarDoctoresRec(std::queue<Doctor>& q) {
		if (q.empty()) return 0;
		Doctor d = q.front();
		q.pop();
		int pago = d.cobrar();
		d.resetEnfermedadesSinPagar();
		int resto = pagarDoctoresRec(q);
		q.push(d); // restauramos en el orden original al volver
		return pago + resto;
	}

	std::list<Medicamento> Hospital::reponerStock_k(int k) const {
		std::list<Medicamento> res;
		for (const auto& m : *almacen) {
			int necesario = k - m.getCantidad();
			if (necesario < 0) necesario = 0;
			res.emplace_back(m.getID(), m.getNombre(), m.getTipo(), necesario);
		}
		return res;
	}

	std::list<Medicamento> Hospital::reponerStock_niveles(const std::list<Medicamento>& nivelesAdecuados) const {
		std::list<Medicamento> res;
		for (const auto& nivel : nivelesAdecuados) {
			// buscar por id en el almacen
			int actual = 0;
			for (const auto& m : *almacen) {
				if (m.getID() == nivel.getID()) { actual = m.getCantidad(); break; }
			}
			int necesario = nivel.getCantidad() - actual;
			if (necesario < 0) necesario = 0;
			res.emplace_back(nivel.getID(), nivel.getNombre(), nivel.getTipo(), necesario);
		}
		return res;
	}

	std::pair<Doctor, Paciente> Hospital::treatPaciente() {
		if (doctores->empty() || urgencias->empty()) return std::make_pair(Doctor(), Paciente());
		Doctor d = doctores->front(); doctores->pop();
		Paciente p = urgencias->top(); urgencias->pop();


		p.tratarEnfermedad(d);


		if (!p.getEnfermedades().empty()) {
			urgencias->push(p);
		}
		else {
			p.darAlta(d);
		}


		doctores->push(d);
		return std::make_pair(d, p);
	}

	int Hospital::pagarDoctores() {
		std::queue<Doctor> copia = *doctores;
		int total = pagarDoctoresRec(copia);
		std::queue<Doctor> temp;
		while (!doctores->empty()) {
			Doctor d = doctores->front(); doctores->pop();
			d.resetEnfermedadesSinPagar();
			temp.push(d);
		}
		*doctores = std::move(temp);
		return total;
	}

}