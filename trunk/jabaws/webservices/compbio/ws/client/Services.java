/* Copyright (c) 2009 Peter Troshin
 *  
 *  JAva Bioinformatics Analysis Web Services (JABAWS) @version: 1.0     
 * 
 *  This library is free software; you can redistribute it and/or modify it under the terms of the
 *  Apache License version 2 as published by the Apache Software Foundation
 * 
 *  This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 *  even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the Apache 
 *  License for more details.
 * 
 *  A copy of the license is in apache_license.txt. It is also available here:
 * @see: http://www.apache.org/licenses/LICENSE-2.0.txt
 * 
 * Any republication or derived work distributed in source code form
 * must include this copyright and license notice.
 */

package compbio.ws.client;

import java.io.File;
import java.net.URL;
import java.util.Set;

import javax.xml.namespace.QName;
import javax.xml.ws.Service;

import compbio.data.msa.JABAService;
import compbio.data.msa.MsaWS;
import compbio.data.msa.SequenceAnnotation;
import compbio.engine.client.ConfExecutable;
import compbio.engine.client.Executable;
import compbio.runner.conservation.AACon;
import compbio.runner.disorder.Disembl;
import compbio.runner.disorder.GlobPlot;
import compbio.runner.disorder.IUPred;
import compbio.runner.disorder.Jronn;
import compbio.runner.msa.ClustalW;
import compbio.runner.msa.Mafft;
import compbio.runner.msa.Muscle;
import compbio.runner.msa.Probcons;
import compbio.runner.msa.Tcoffee;

/**
 * List of web services currently supported by JABAWS version 2
 * 
 */
public enum Services {
	MafftWS, MuscleWS, ClustalWS, TcoffeeWS, ProbconsWS, AAConWS, JronnWS, DisemblWS, GlobPlotWS, IUPredWS;

	public static Services getService(String servName) {
		servName = servName.trim().toLowerCase();
		for (Services service : Services.values()) {
			if (service.toString().equalsIgnoreCase(servName)) {
				return service;
			}
		}
		return null;
	}

	public static Services getServiceByRunner(
			Class<Executable<?>> runnerClassName) {
		assert runnerClassName != null;
		String sname = runnerClassName.getSimpleName().toLowerCase();
		for (Services service : Services.values()) {
			if (service.toString().toLowerCase().contains(sname)) {
				return service;
			}
		}
		return null;
	}

	public Class<? extends Executable<?>> getServiceImpl() {
		switch (this) {
			case AAConWS :
				return AACon.class;
			case ClustalWS :
				return ClustalW.class;
			case MafftWS :
				return Mafft.class;
			case MuscleWS :
				return Muscle.class;
			case TcoffeeWS :
				return Tcoffee.class;
			case ProbconsWS :
				return Probcons.class;
			case DisemblWS :
				return Disembl.class;
			case GlobPlotWS :
				return GlobPlot.class;
			case JronnWS :
				return Jronn.class;
			case IUPredWS :
				return IUPred.class;
			default :
				throw new RuntimeException(
						"Unknown web service implementation class for service: "
								+ this);
		}
	}

	public static Class<? extends Executable<?>> getRunnerByJobDirectory(
			File jobdir) {
		Services service = getServiceByRunnerName(getRunnerNameByJobDirectory(jobdir));
		return service.getServiceImpl();
	}

	private static String getRunnerNameByJobDirectory(File jobdir) {
		String name = jobdir.getName().split("#")[0];

		if (name.startsWith(ConfExecutable.CLUSTER_TASK_ID_PREFIX)) {
			assert ConfExecutable.CLUSTER_TASK_ID_PREFIX.length() == 1;
			name = name.substring(1);
		}
		return name;
	}

	public static Services getServiceByJobDirectory(File jobdir) {
		return getServiceByRunnerName(getRunnerNameByJobDirectory(jobdir));
	}

	private static Services getServiceByRunnerName(String name) {
		for (Services service : Services.values()) {
			String runnerName = service.getServiceImpl().getSimpleName()
					.toLowerCase();
			name = name.trim().toLowerCase();
			if (name.startsWith(runnerName)) {
				return service;
			}
		}
		return null;
	}

	Service getService(URL url, String sqname) {
		QName qname = new QName(sqname, this.toString());
		return Service.create(url, qname);
	}

	public static String toString(Set<Services> services) {
		if (services == null || services.isEmpty()) {
			return "";
		}
		String value = "";
		String delim = ", ";
		for (Services serv : services) {
			value += serv.toString() + delim;
		}
		value = value.substring(0, value.length() - delim.length());
		return value;
	}

	Class<? extends JABAService> getServiceType() {
		switch (this) {
			// deliberate leaking
			case AAConWS :
			case JronnWS :
			case DisemblWS :
			case GlobPlotWS :
			case IUPredWS :
				return SequenceAnnotation.class;

				// deliberate leaking
			case ClustalWS :
			case MafftWS :
			case MuscleWS :
			case ProbconsWS :
			case TcoffeeWS :

				return MsaWS.class;
			default :
				throw new RuntimeException("Unrecognised Web Service Type "
						+ this + " - Should never happened!");
		}
	}

	JABAService getInterface(Service service) {
		assert service != null;

		QName portName = new QName(service.getServiceName().getNamespaceURI(),
				this.toString() + "Port");
		return service.getPort(portName, this.getServiceType());
	}
}