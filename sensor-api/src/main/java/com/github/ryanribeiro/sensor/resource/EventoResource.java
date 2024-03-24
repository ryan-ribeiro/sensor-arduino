package com.github.ryanribeiro.sensor.resource;


import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import com.github.ryanribeiro.sensor.domain.Evento;
import com.github.ryanribeiro.sensor.dto.EventoDTO;
import com.github.ryanribeiro.sensor.services.EventoServices;

@RestController
@RequestMapping("eventos")
public class EventoResource{
	
	@Autowired
	private EventoServices eventoServices;
	
	@GetMapping
	public ResponseEntity<List<Evento>> listar() {
		return ResponseEntity.ok(eventoServices.listar());
	}
		
	@PostMapping()
	public ResponseEntity<Void> salvar(@RequestBody EventoDTO eventoDTO) {
		
		eventoServices.salvar(eventoDTO);
		
		return ResponseEntity
					.status(HttpStatus.CREATED)
					.build();
	}
}
