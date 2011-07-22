package compbio.ws.server;

import java.util.List;

import org.apache.log4j.Logger;

import compbio.data.sequence.FastaSequence;
import compbio.engine.Configurator;
import compbio.engine.client.ConfiguredExecutable;
import compbio.engine.client.Executable;
import compbio.engine.client.SkeletalExecutable;
import compbio.metadata.ChunkHolder;
import compbio.metadata.JobStatus;
import compbio.metadata.JobSubmissionException;
import compbio.metadata.Limit;
import compbio.metadata.LimitsManager;
import compbio.metadata.PresetManager;
import compbio.metadata.RunnerConfig;
import compbio.runner.Util;

public abstract class GenericMetadataService<T> {

	private final RunnerConfig<T> aaconOptions;
	private final PresetManager<T> aaconPresets;
	private final LimitsManager<T> limitMan;
	private SkeletalExecutable<T> exec;
	final Logger log;

	/*
	 * FIXME - instances of the Runner (?) and their types should be defined in
	 * Executable IF
	 */
	GenericMetadataService(SkeletalExecutable<T> exec, Logger log) {
		assert log != null;
		assert exec != null;
		this.log = log;
		this.exec = exec;
		this.limitMan = compbio.engine.client.Util.getLimits(exec.getType());
		this.aaconOptions = Util
				.getSupportedOptions((Class<? extends Executable<T>>) exec
						.getType());
		this.aaconPresets = Util
				.getPresets((Class<? extends Executable<T>>) exec.getType());
	}

	ConfiguredExecutable<T> init(List<FastaSequence> sequences)
			throws JobSubmissionException {
		// FIXME
		try {
			exec = (SkeletalExecutable<T>) exec.getType().newInstance();
		} catch (InstantiationException e) {
			log.error(e.getLocalizedMessage(), e);
			throw new JobSubmissionException(e.getLocalizedMessage(), e);
		} catch (IllegalAccessException e) {
			log.error(e.getLocalizedMessage(), e);
			throw new JobSubmissionException(e.getLocalizedMessage(), e);
		}
		exec.setInput(SkeletalExecutable.INPUT)
				.setOutput(SkeletalExecutable.OUTPUT)
				.setError(SkeletalExecutable.ERROR);
		return Configurator.configureExecutable(exec, sequences);
	}

	public boolean cancelJob(String jobId) {
		WSUtil.validateJobId(jobId);
		return WSUtil.cancelJob(jobId);
	}

	public JobStatus getJobStatus(String jobId) {
		WSUtil.validateJobId(jobId);
		return WSUtil.getJobStatus(jobId);
	}

	public Limit<T> getLimit(String presetName) {
		if (limitMan == null) {
			// Limit is not defined
			return null;
		}
		return limitMan.getLimitByName(presetName);
	}

	public LimitsManager<T> getLimits() {
		return limitMan;
	}

	public PresetManager<T> getPresets() {
		return aaconPresets;
	}

	public RunnerConfig<T> getRunnerOptions() {
		return aaconOptions;
	}

	/**
	 * Assume statistics is not supported
	 * 
	 * @param jobId
	 * @param position
	 * @return
	 */
	public ChunkHolder pullExecStatistics(String jobId, long position) {
		// Execution stat is not supported
		return new ChunkHolder("", -1);
	}

}
