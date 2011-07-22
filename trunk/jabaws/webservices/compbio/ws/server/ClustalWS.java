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

package compbio.ws.server;

import java.io.File;
import java.util.List;

import javax.jws.WebService;

import org.apache.log4j.Logger;

import compbio.data.msa.JABAService;
import compbio.data.msa.MsaWS;
import compbio.data.sequence.Alignment;
import compbio.data.sequence.FastaSequence;
import compbio.engine.AsyncExecutor;
import compbio.engine.Configurator;
import compbio.engine.client.ConfiguredExecutable;
import compbio.engine.client.SkeletalExecutable;
import compbio.metadata.ChunkHolder;
import compbio.metadata.JobStatus;
import compbio.metadata.JobSubmissionException;
import compbio.metadata.Limit;
import compbio.metadata.LimitsManager;
import compbio.metadata.Option;
import compbio.metadata.Preset;
import compbio.metadata.PresetManager;
import compbio.metadata.ResultNotAvailableException;
import compbio.metadata.RunnerConfig;
import compbio.metadata.WrongParameterException;
import compbio.runner.Util;
import compbio.runner.msa.ClustalW;

@WebService(endpointInterface = "compbio.data.msa.MsaWS", targetNamespace = JABAService.SERVICE_NAMESPACE, serviceName = "ClustalWS")
public class ClustalWS implements MsaWS<ClustalW> {

	private static Logger log = Logger.getLogger(ClustalWS.class);

	private static final RunnerConfig<ClustalW> clustalOptions = Util
			.getSupportedOptions(ClustalW.class);

	private static final PresetManager<ClustalW> clustalPresets = Util
			.getPresets(ClustalW.class);

	private static final LimitsManager<ClustalW> limitMan = compbio.engine.client.Util
			.getLimits(new ClustalW().getType());

	@Override
	public String align(List<FastaSequence> sequences)
			throws JobSubmissionException {

		WSUtil.validateFastaInput(sequences);
		ConfiguredExecutable<ClustalW> confClust = init(sequences);
		return WSUtil.align(sequences, confClust, log, "align", getLimit(""));
	}

	ConfiguredExecutable<ClustalW> init(List<FastaSequence> dataSet)
			throws JobSubmissionException {
		ClustalW clustal = new ClustalW();
		clustal.setInput(SkeletalExecutable.INPUT)
				.setOutput(SkeletalExecutable.OUTPUT)
				.setError(SkeletalExecutable.ERROR);
		ConfiguredExecutable<ClustalW> confClust = Configurator
				.configureExecutable(clustal, dataSet);
		return confClust;
	}

	@Override
	public String presetAlign(List<FastaSequence> sequences,
			Preset<ClustalW> preset) throws JobSubmissionException,
			WrongParameterException {
		WSUtil.validateFastaInput(sequences);
		if (preset == null) {
			throw new WrongParameterException("Preset must be provided!");
		}
		Limit<ClustalW> limit = getLimit(preset.getName());
		ConfiguredExecutable<ClustalW> confClust = init(sequences);
		confClust.addParameters(preset.getOptions());
		return WSUtil.align(sequences, confClust, log, "presetAlign", limit);
	}

	@Override
	public String customAlign(List<FastaSequence> sequences,
			List<Option<ClustalW>> options) throws JobSubmissionException,
			WrongParameterException {
		WSUtil.validateFastaInput(sequences);
		ConfiguredExecutable<ClustalW> confClust = init(sequences);
		List<String> params = WSUtil.getCommands(options,
				ClustalW.KEY_VALUE_SEPARATOR);
		confClust.addParameters(params);
		log.info("Setting parameters: " + params);
		return WSUtil.align(sequences, confClust, log, "customAlign",
				getLimit(""));
	}

	@Override
	public RunnerConfig<ClustalW> getRunnerOptions() {
		return clustalOptions;
	}

	@SuppressWarnings("unchecked")
	@Override
	public Alignment getResult(String jobId) throws ResultNotAvailableException {

		WSUtil.validateJobId(jobId);
		AsyncExecutor asyncEngine = Configurator.getAsyncEngine(jobId);
		ConfiguredExecutable<ClustalW> clustal = (ConfiguredExecutable<ClustalW>) asyncEngine
				.getResults(jobId);
		Alignment al = clustal.getResults();

		return al;
	}

	@Override
	public Limit<ClustalW> getLimit(String presetName) {
		if (limitMan == null) {
			// No limit is configured
			return null;
		}
		Limit<ClustalW> limit = limitMan.getLimitByName(presetName);
		return limit;
	}

	@Override
	public LimitsManager<ClustalW> getLimits() {
		return limitMan;
	}

	@Override
	public boolean cancelJob(String jobId) {
		WSUtil.validateJobId(jobId);
		boolean result = WSUtil.cancelJob(jobId);
		return result;
	}

	@Override
	public JobStatus getJobStatus(String jobId) {
		WSUtil.validateJobId(jobId);
		JobStatus status = WSUtil.getJobStatus(jobId);
		return status;
	}

	@Override
	public PresetManager<ClustalW> getPresets() {
		return clustalPresets;
	}

	@Override
	public ChunkHolder pullExecStatistics(String jobId, long position) {

		WSUtil.validateJobId(jobId);
		String file = Configurator.getWorkDirectory(jobId) + File.separator
				+ ClustalW.getStatFile();
		ChunkHolder cholder = WSUtil.pullFile(file, position);
		return cholder;
	}

}
