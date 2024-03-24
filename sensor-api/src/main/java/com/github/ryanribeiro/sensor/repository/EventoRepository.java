package com.github.ryanribeiro.sensor.repository;


import org.springframework.data.jpa.repository.JpaRepository;

import com.github.ryanribeiro.sensor.domain.Evento;

public interface EventoRepository extends JpaRepository<Evento, Long>{

}
